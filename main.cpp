#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>

using namespace std;

class FinanceManager
{
};

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
    void addCategory(Category category){
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
        for(auto e : categories){
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
        stack<Transaction> recentTransactions;
    public:
        TransactionManager(CategoryManager& incomingManager)
            : categoryManager(incomingManager) {}

        void addTransaction(Transaction transaction){
            // Grab current category
            Category& currentCategory = categoryManager.getCategory(transaction.category);
            currentCategory.spent += transaction.amount;
            recentTransactions.push(transaction);
        }

        void removeTransaction(Transaction transaction){
            // Grab current category
            Category& currentCategory = categoryManager.getCategory(transaction.category);
            // Multiply by negative 1 to add it back
            currentCategory.spent += (transaction.amount * -1);
        }

        void undo(){
            // Check to see if its empty
            if(recentTransactions.empty()){
                cout << "Nothing to undo" << endl;
                return;
            }else{
                // Grab the most recent transaction from the stack and pop it.
                Transaction currentTransacton = recentTransactions.top();
                recentTransactions.pop();

                // Call remove transaction
                removeTransaction(currentTransacton);
            }
            

        }
};

int main(){

    Category fixed{"Fixed",1800.00,0.00};
    Category entertainment{"Entertainment",500,0.00};
    Category groceries{"Groceries",500,0.00};

    Transaction expense{
        0,
        850,
        "Fixed",
        "Thats how much I pay for rent",
        "Today"
    };

    // Create CategoryManager
    CategoryManager test;

    // Add categories
    test.addCategory(fixed);
    test.addCategory(entertainment);
    test.addCategory(groceries);

    // Pass the existing CategoryManager into TransactionManager
    TransactionManager tester(test);

    // Add transaction
    tester.addTransaction(expense);

    // Print updated category
    test.printCategoryDetails(expense.category);
    tester.undo();
    test.printCategoryDetails(expense.category);
    tester.undo();
}