//
// Created by Owen Morgan on 05/11/2024.
//

#include "Ingredient.h"

#ifndef EE2010_GROUP_MY_SCRATCH_RECIPE_H
#define EE2010_GROUP_MY_SCRATCH_RECIPE_H

class Recipe
{
public:
    Recipe(std::string title);
    void add_ingredient(const Ingredient &ingredient);
    void display_recipe_ingredients() const;

private:
    std::string title;
    std::vector<Ingredient> ingredients;

};


#endif //EE2010_GROUP_MY_SCRATCH_RECIPE_H
