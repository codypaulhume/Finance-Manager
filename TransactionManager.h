#pragma once

#include "Transaction.h"
#include "CategoryManager.h"

#include <vector>

class TransactionManager
{
private:
    CategoryManager& categoryManager;
    std::vector<Transaction> allTransactions;

public:
    TransactionManager(CategoryManager& incomingManager);

    void addTransaction(const Transaction& transaction);
    void removeTransaction(const Transaction& transaction);

    void printTransactions();
};
