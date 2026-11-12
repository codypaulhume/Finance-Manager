#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <stack>
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
        // Storing the category using the name as its key, and the argument as the value
        categories[category.name] = category;
    }

    void removeCategory(string name){
        categories.erase(name);
    }

    Category& getCategory(string name){
        return categories[name];
    }

    void printCategories(){
        for(const auto& e : categories){
            cout << e.first << endl;
        }
    }

    void printCategoryDetails(string name){
        Category currentCategory = categories[name];
        cout << currentCategory.name << endl;
        cout << currentCategory.allocated << endl;
        cout << currentCategory.spent << endl;
        cout << currentCategory.getRemaining() << endl;
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
            // Grab current category
            Category& currentCategory = categoryManager.getCategory(transaction.category);
            currentCategory.spent += transaction.amount;
            // Add to all transactions and recent transactions
            allTransactions.push_back(transaction);
        }

        void removeTransaction(const Transaction& transaction){

            auto iterator = find_if(allTransactions.begin(), allTransactions.end(), [&transaction](const Transaction& t)
            {return t.id == transaction.id;});

            // If we didn't find the transaction matching the id
            if(iterator == allTransactions.end()){
                cout << "Transaction not found" << endl;
                return;
            }

            // Grab current category
            Category& currentCategory = categoryManager.getCategory(iterator->category);

            // Multiply by negative 1 to add it back
            currentCategory.spent += (iterator->amount * -1);

            allTransactions.erase(iterator);
        }

        void printTransactions(){
            for(const auto& transaction : allTransactions){
                cout << transaction.id << endl;
            }
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

    void removeCategory(string category){
        categoryManager.removeCategory(category);
    }

    void printCategories(){
        categoryManager.printCategories();
    }

    void printCategoryDetails(string name){
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
    financeManager.addCategory(entertainment);
    financeManager.addCategory(groceries);
    financeManager.printCategories();

    financeManager.addTransaction(expense);
    financeManager.addTransaction(expenseTwo);
    // financeManager.printCategoryDetails("Fixed");
    financeManager.printTransactions();
    financeManager.removeTransaction(expense);
    financeManager.printTransactions();
}