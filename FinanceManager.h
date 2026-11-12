#pragma once

#include "CategoryManager.h"
#include "TransactionManager.h"

#include <string>

class FinanceManager
{
private:
    CategoryManager categoryManager;
    TransactionManager transactionManager;

public:
    FinanceManager();

    void addCategory(const Category& category);
    void removeCategory(const std::string& name);

    void printCategories();
    void printCategoryDetails(const std::string& name);

    void addTransaction(const Transaction& transaction);
    void removeTransaction(const Transaction& transaction);

    void printTransactions();
};
