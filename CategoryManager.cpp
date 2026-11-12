#include "CategoryManager.h"

#include <iostream>

void CategoryManager::addCategory(const Category& category)
{
    if (categories.count(category.name) > 0)
    {
        std::cout << "Category already exists" << std::endl;
        return;
    }

    categories[category.name] = category;
}

void CategoryManager::removeCategory(const std::string& name)
{
    categories.erase(name);
}

Category* CategoryManager::getCategory(const std::string& name)
{
    auto iterator = categories.find(name);

    if (iterator == categories.end())
    {
        return nullptr;
    }

    return &iterator->second;
}

void CategoryManager::printCategories()
{
    for (const auto& e : categories)
    {
        std::cout << e.first << std::endl;
    }
}

void CategoryManager::printCategoryDetails(const std::string& name)
{
    Category* category = getCategory(name);

    if (category == nullptr)
    {
        std::cout << "Category not found" << std::endl;
        return;
    }

    std::cout << "Name: " << category->name << std::endl;
    std::cout << "Allocated: " << category->allocated << std::endl;
    std::cout << "Spent: " << category->spent << std::endl;
    std::cout << "Remaining: " << category->getRemaining() << std::endl;
}
