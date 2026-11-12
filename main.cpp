#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct Category
{
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
    unordered_map<string, Category> categories;

public:
    void addCategory(const Category& category){
        // If category exists, do not add
        if(categories.count(category.name) > 0){
            cout << "Category already exists" << endl;
            return;
        }

        // Add new category to map
        categories[category.name] = category;
    }

    void removeCategory(const string& name){
        categories.erase(name);
    }

    Category* getCategory(const string& name){
        auto iterator = categories.find(name);

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

    void printCategoryDetails(const string& name){
        cout << "Category Details:" << endl;
        Category* currentCategory = getCategory(name);
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
    
};

struct Transaction{
    int id;
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
            // Check if transaction with that ID already exists
            auto iterator = find_if(allTransactions.begin(), allTransactions.end(), [&transaction](const Transaction& t){
                return t.id == transaction.id;
            });

            // If we find a duplicate ID - Bad
            if(iterator != allTransactions.end()){
                cout << "Duplicate transaction ID. Please ensure all transaction IDs are unique." << endl;
                return;
            }

            // Grab current category
            Category* currentCategory = categoryManager.getCategory(transaction.category);

            // Check to see if category exists
            if(currentCategory == nullptr){
                cout << "Coudln't find the correct category" << endl;
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

            // Grab current category
            Category* currentCategory = categoryManager.getCategory(iterator->category);

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

    void removeCategory(const string& category){
        categoryManager.removeCategory(category);
    }

    void printCategories(){
        categoryManager.printCategories();
    }

    void printCategoryDetails(const string& name){
        categoryManager.printCategoryDetails(name);
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
};

int main(){

    Category fixed{"Fixed",1800.00,0.00};
    Category entertainment{"Entertainment",500,0.00};
    Category groceries{"Groceries",500,0.00};

    Transaction expense{0,850,"Fixed","Thats how much I pay for rent","Today"};
    Transaction expenseTwo{1,850,"Fixed","Thats how much I pay for rent","Today"};
    
    FinanceManager financeManager;

    financeManager.addCategory(fixed);
    // Testing duplicate categories
    financeManager.addCategory(fixed);
    financeManager.addCategory(entertainment);
    financeManager.addCategory(groceries);

    financeManager.addTransaction(expense);
    // Testing duplicate transaction ID
    financeManager.addTransaction(expense);
    financeManager.addTransaction(expenseTwo);
    financeManager.printCategoryDetails("Fixed");

    financeManager.printTransactions();

    financeManager.removeTransaction(expense);
    financeManager.printTransactions();
    financeManager.printCategoryDetails("Fixed");
}