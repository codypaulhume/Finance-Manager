#include "FinanceManager.h"

FinanceManager::FinanceManager()
    : categoryManager(),
      transactionManager(categoryManager)
{
}

void FinanceManager::addCategory(const Category& category)
{
    categoryManager.addCategory(category);
}

void FinanceManager::removeCategory(const std::string& name)
{
    categoryManager.removeCategory(name);
}

void FinanceManager::printCategories()
{
    categoryManager.printCategories();
}

void FinanceManager::printCategoryDetails(const std::string& name)
{
    categoryManager.printCategoryDetails(name);
}

void FinanceManager::addTransaction(const Transaction& transaction)
{
    transactionManager.addTransaction(transaction);
}

void FinanceManager::removeTransaction(const Transaction& transaction)
{
    transactionManager.removeTransaction(transaction);
}

void FinanceManager::printTransactions()
{
    transactionManager.printTransactions();
}
