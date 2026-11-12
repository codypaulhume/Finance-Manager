#pragma once

#include <string>

struct Transaction
{
    int id;
    double amount;
    std::string category;
    std::string description;
    std::string date;
};
