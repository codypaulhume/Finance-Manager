#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct Category
{
        int id;
        string name;
        double allocated;
        double spent;
        double getRemaining() const{
            return allocated - spent;
        }
};

class CategoryManager
{
private:
    // Stores all categories and their values
    unordered_map<int, Category> categories;

public:
    void addCategory(const Category& category){
        // If category exists, do not add
        if(categories.count(category.id) > 0){
            cout << "Category already exists" << endl;
            return;
        }

        // Add new category to map
        categories[category.id] = category;
    }

    void removeCategory(const int& id){
        categories.erase(id);
    }

    Category* getCategory(const int& id){
        auto iterator = categories.find(id);

        if(iterator == categories.end()){
            return nullptr;
        }

        // Found the category
        return &iterator->second;
    }

    void printCategories(){
        for(const auto& e : categories){
            cout << e.first << endl;
        }
        cout << "----------" << endl;
    }

    // Taking objects from UM and pushing them into a vector. This will be used for the financial summary.
    vector<Category> getAllCategories() const{
        vector<Category> result;
        for(auto it : categories){
            result.push_back(it.second);
        }
        return result;
    }

    void printCategoryDetails(const int& id){
        cout << "Category Details:" << endl;
        Category* currentCategory = getCategory(id);
        // Check if category exists
        if(currentCategory == nullptr){
            cout << "Category not found" << endl;
            return; 
        }
        cout << "Category: " << currentCategory->name << endl;
        cout << "Allocated: " << currentCategory->allocated << endl;
        cout << "Spent: " << currentCategory->spent << endl;
        cout << "Remaining: " << currentCategory->getRemaining() << endl;
        cout << "----------" << endl;
    }

    double getTotalAllocated() const{
        double res = 0;
        for(const auto& it : categories){
            res += it.second.allocated;
        }
        return res;
    }

    string getTopSpendingCategory(){
        double ratio = 0;
        double topRatio = 0;
        string topCategory = "";

        for(const auto& it : categories){
            if(it.second.allocated != 0){
                if(it.second.spent > 0){
                ratio = (it.second.spent / it.second.allocated) * 100;
                }
                if(ratio >= topRatio){
                    topCategory = it.second.name;
                }
                topRatio = max(ratio, topRatio);

                // Reset ratio
                ratio = 0;
            }
        }

        // Check if no money was spent
        if(topRatio == 0){
            return "No top spending category";
        }

        return topCategory;
    }
};

struct Transaction{
    int id;
    int categoryID;
    double amount;
    string category;
    string description;
    string date;
};

class TransactionManager{
    private:
        CategoryManager& categoryManager;
        vector<Transaction> allTransactions;
    public:
        TransactionManager(CategoryManager& incomingManager)
            : categoryManager(incomingManager) {}

        void addTransaction(const Transaction& transaction){
            // Check if transaction with duplicate ID already exists
            auto iterator = find_if(allTransactions.begin(), allTransactions.end(), [&transaction](const Transaction& t){
                return t.id == transaction.id;
            });

            // If we find a duplicate ID - Bad
            if(iterator != allTransactions.end()){
                cout << "Duplicate transaction ID. Please ensure all transaction IDs are unique." << endl;
                return;
            }

            // Grab current category
            Category* currentCategory = categoryManager.getCategory(transaction.categoryID);

            // Check to see if category exists
            if(currentCategory == nullptr){
                cout << "Coudln't find the correct category" << endl;
                return;
            }

            if(transaction.amount <= 0){
                cout << "Amount must be greater than 0" << endl;
                return;
            }

            currentCategory->spent += transaction.amount;
            // Add to all transactions vector
            allTransactions.push_back(transaction);
            
        }

        void removeTransaction(const Transaction& transaction){

            auto iterator = find_if(allTransactions.begin(), allTransactions.end(), [&transaction](const Transaction& t){
                return t.id == transaction.id;});

            // If we didn't find the transaction matching the id
            if(iterator == allTransactions.end()){
                cout << "Transaction not found" << endl;
                return;
            }

            // Grab current category using its Category ID. These two should match
            Category* currentCategory = categoryManager.getCategory(iterator->categoryID);

            // Check to see if category exists
            if(currentCategory == nullptr){
                cout << "Coudln't find the correct category" << endl;
                return;
            }
            // Subtract ammount from spent variable
            currentCategory->spent -= (iterator->amount);

            allTransactions.erase(iterator);
        }

        void printTransactions(){
            cout << "Transaction IDs:" << endl;
            for(const auto& transaction : allTransactions){
                cout << transaction.id << endl;
            }
            cout << "----------" << endl;
        }
        
        bool checkCategory(const int& category){
            auto iterator = find_if(allTransactions.begin(), allTransactions.end(), [&category](const Transaction &t){
                return t.categoryID == category;
            });

            return iterator != allTransactions.end();
        }

        double getTotalSpent() const{
            double res = 0;
            for(const auto& it : allTransactions){
                res += it.amount;
            }
            return res;
        }

        vector<Transaction> getAllTransactions() const{
            return allTransactions;
        }
};

struct FinancialSummary{
    double totalAllocated;
    double totalSpent;
    double getTotalRemaining() const{
        return totalAllocated - totalSpent;
    }
    vector<Category> categories;
    vector<Transaction> allTransactions;
    string topSpendingCategory;
};

class FinanceManager
{
private:
    CategoryManager categoryManager;
    TransactionManager transactionManager;

public:
    FinanceManager()
        : categoryManager(),
          transactionManager(categoryManager) {}

    void addCategory(const Category& category){
        categoryManager.addCategory(category);
    }

    void removeCategory(const int& category){
        if(transactionManager.checkCategory(category)){
            cout << "Cannot remove category. Transaction with category exists" << endl;
            return;
        }
        categoryManager.removeCategory(category);
    }

    void printCategories(){
        categoryManager.printCategories();
    }

    void printCategoryDetails(const int& id){
        categoryManager.printCategoryDetails(id);
    }

    void addTransaction(const Transaction& transaction){
        transactionManager.addTransaction(transaction);
    }

    void removeTransaction(const Transaction& transaction){
        transactionManager.removeTransaction(transaction);
    }

    void printTransactions(){
        transactionManager.printTransactions();
    }

    vector<Transaction> getAllTransactions(){
        return transactionManager.getAllTransactions();
    }

    void printAllTransactions(){
        // Cout for C++ purposes
        vector<Transaction> res = transactionManager.getAllTransactions();

        cout << "--------------------------------------" << endl;
        cout << "           All Transactions" << endl;
        cout << "--------------------------------------" << endl;
        for(const auto& it : res){
            cout << "Category: " << it.category << ", Description: " << it.description << ", Amount: $" << it.amount << ", Date: " << it.date << endl;
        }
        return;
    }

    FinancialSummary getFinancialSummary(){
        FinancialSummary summary{categoryManager.getTotalAllocated(), transactionManager.getTotalSpent(), categoryManager.getAllCategories(), transactionManager.getAllTransactions(), categoryManager.getTopSpendingCategory()};
        return summary;
    }

    void printFinancialSummary(){
        FinancialSummary summary = getFinancialSummary();
        cout << "--------------------------------------" << endl;
        cout << "         Financial Summary" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Total Allocated: $" << summary.totalAllocated << endl;
        cout << "Total Spent: $" << summary.totalSpent << endl;
        cout << "Total Remaining: $" << summary.getTotalRemaining() << endl;
        cout << "Top Spending Category: " << summary.topSpendingCategory << endl;
        cout << "--------------------------------------" << endl;
        cout << "         Breakdown by Category" << endl;
        cout << "--------------------------------------" << endl;
        for(const auto& category : summary.categories){
            cout << "Category: " << category.name << endl;
            cout << "Total Allocated: $" << category.allocated << endl;
            cout << "Total Spent: $" << category.spent << endl;
            cout << "Total Remaining: $" << category.getRemaining() << endl;
            cout << "------------------" << endl;
        }

        // Print all transactions
        cout << "--------------------------------------" << endl;
        cout << "           All Transactions" << endl;
        cout << "--------------------------------------" << endl;
        for(const auto& it : summary.allTransactions){
            cout << "Category: " << it.category << ", Description: " << it.description << ", Amount: $" << it.amount << ", Date: " << it.date << endl;
        }
        return;
    }
};

int main(){

    Category fixed{1,"Fixed",1800.00,0.00};
    Category entertainment{2,"Entertainment",500,0.00};
    Category groceries{3,"Groceries",500,0.00};
    Transaction expense{0,1,850,"Fixed","Rent","10/31/26"};
    Transaction expenseTwo{1,2,98.56,"Entertainment","Movie Theater","11/02/26"};
    
    FinanceManager financeManager;

    financeManager.addCategory(fixed);
    financeManager.addCategory(entertainment);
    financeManager.addCategory(groceries);

    financeManager.addTransaction(expense);
    financeManager.addTransaction(expenseTwo);

    //financeManager.printAllTransactions();
    financeManager.printFinancialSummary();
}





// Testing code
// Everything related to category needs to be updated from using its name (string) to id (int)

    // Category fixed{"Fixed",1800.00,0.00};
    // Category entertainment{"Entertainment",500,0.00};
    // Category groceries{"Groceries",500,0.00};

    // Transaction expense{0,850,"Fixed","Thats how much I pay for rent","Today"};
    // Transaction expenseTwo{1,850,"Fixed","Thats how much I pay for rent","Today"};
    
    // FinanceManager financeManager;

    // financeManager.addCategory(fixed);
    // // Testing duplicate categories
    // financeManager.addCategory(fixed);
    // financeManager.addCategory(entertainment);
    // financeManager.addCategory(groceries);

    // financeManager.addTransaction(expense);
    // // Testing duplicate transaction ID
    // financeManager.addTransaction(expense);
    // financeManager.addTransaction(expenseTwo);
    // // Testing check for category removal when expense exists
    // financeManager.removeCategory("Fixed");
    // financeManager.printCategoryDetails("Fixed");

    // financeManager.printTransactions();

    // financeManager.removeTransaction(expense);
    // financeManager.removeTransaction(expenseTwo);
    // financeManager.printTransactions();