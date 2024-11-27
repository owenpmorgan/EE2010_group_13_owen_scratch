//
// Created by Owen Morgan on 26/11/2024.
//

#include "Recipe.h"
#include <map>

#ifndef EE2010_GROUP_MY_SCRATCH_RECIPELIST_H
#define EE2010_GROUP_MY_SCRATCH_RECIPELIST_H


class RecipeList: public Recipe
{
private:
    std::map<int, Recipe> recipes;
    int next_id = 1; // Auto-incrementing ID for recipes

public:
    // Add a recipe to the list and assign a unique ID
    void add_recipe_to_list(const Recipe& recipe);
    // Retrieve a recipe by ID
    Recipe& get_recipe_by_id(int id);
    // print the recipe list
    void display_recipe_list();
    // get the recipe list map
    std::map<int, Recipe> get_recipe_list();
};





#endif //EE2010_GROUP_MY_SCRATCH_RECIPELIST_H
