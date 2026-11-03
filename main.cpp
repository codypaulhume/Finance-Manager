#include <iostream>
#include <unordered_map>
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
    double remaining;
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

    Category getCategory(string name){
        return categories[name];
    }

    void printCategories(){
        for(auto e : categories){
            cout << e.first << endl;
        }
    }
    
};

int main(){
    Category fixed{"Fixed",1800.00,0.00,0.00}; 

    Category entertainment{"Entertainment",500,0.00,0.00};

    Category groceries{"Groceries",500,0.00,0.00};

    // Add these above and test
    CategoryManager test;
    test.addCategory(fixed);
    test.addCategory(entertainment);
    test.printCategories();
    test.removeCategory("Fixed");
    test.printCategories();
}