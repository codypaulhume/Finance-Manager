#include "TransactionManager.h"

#include <algorithm>
#include <iostream>

TransactionManager::TransactionManager(CategoryManager& incomingManager)
    : categoryManager(incomingManager)
{
}

void TransactionManager::addTransaction(const Transaction& transaction)
{
    auto iterator = std::find_if(
        allTransactions.begin(),
        allTransactions.end(),
        [&](const Transaction& current)
        {
            return current.id == transaction.id;
        }
    );

    if (iterator != allTransactions.end())
    {
        std::cout << "Transaction ID already exists" << std::endl;
        return;
    }

    Category* currentCategory =
        categoryManager.getCategory(transaction.category);

    if (currentCategory == nullptr)
    {
        std::cout << "Category does not exist" << std::endl;
        return;
    }

    currentCategory->spent += transaction.amount;
    allTransactions.push_back(transaction);
}

void TransactionManager::removeTransaction(const Transaction& transaction)
{
    auto iterator = std::find_if(
        allTransactions.begin(),
        allTransactions.end(),
        [&](const Transaction& current)
        {
            return current.id == transaction.id;
        }
    );

    if (iterator == allTransactions.end())
    {
        std::cout << "Transaction not found" << std::endl;
        return;
    }

    Category* currentCategory =
        categoryManager.getCategory(iterator->category);

    if (currentCategory == nullptr)
    {
        std::cout << "Category not found" << std::endl;
        return;
    }

    currentCategory->spent -= iterator->amount;
    allTransactions.erase(iterator);
}

void TransactionManager::printTransactions()
{
    for (const auto& transaction : allTransactions)
    {
        std::cout << "Transaction ID: " << transaction.id << std::endl;
    }
}
