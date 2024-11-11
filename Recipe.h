//
// Created by Owen Morgan on 05/11/2024.
//

#include "Ingredient.h"
#include "IngredientList.h"

#ifndef EE2010_GROUP_MY_SCRATCH_RECIPE_H
#define EE2010_GROUP_MY_SCRATCH_RECIPE_H

class Recipe : public IngredientList
{

private:
    std::string title;
    std::unordered_map<int, std::optional<int>> recipe_ingredients;

public:
    Recipe(std::string title);
    Recipe() : title("Unnamed Recipe") {}  // Default constructor
    void add_ingredient(const int uuid, int amount);
    void add_ingredient(const int uuid);
    std::string get_title() const;
    std::unordered_map<int, std::optional<int>> get_recipe_ingredients();
    void display_recipe_ingredients() const;
    std::optional<int> get_amount(int);
};


#endif //EE2010_GROUP_MY_SCRATCH_RECIPE_H
