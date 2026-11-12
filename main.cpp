#include "FinanceManager.h"

#include <iostream>

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
