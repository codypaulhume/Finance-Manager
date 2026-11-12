#pragma once

#include <string>

struct Category
{
    std::string name;
    double allocated;
    double spent;

    double getRemaining() const
    {
        return allocated - spent;
    }
};
