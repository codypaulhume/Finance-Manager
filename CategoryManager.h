#pragma once

#include "Category.h"

#include <string>
#include <unordered_map>

class CategoryManager
{
private:
    std::unordered_map<std::string, Category> categories;

public:
    void addCategory(const Category& category);
    void removeCategory(const std::string& name);

    Category* getCategory(const std::string& name);

    void printCategories();
    void printCategoryDetails(const std::string& name);
};
