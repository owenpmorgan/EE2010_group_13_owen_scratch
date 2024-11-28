//
// Created by Owen Morgan on 26/11/2024.
//

#include "RecipeList.h"

void RecipeList::add_recipe_to_list(const Recipe& recipe)
{
    recipes[next_id++] = recipe;
}

Recipe& RecipeList::get_recipe_by_id(int id)
{
    if (recipes.find(id) == recipes.end()) {
        throw std::runtime_error("Recipe with ID " + std::to_string(id) + " not found.");
    }
    return recipes[id];
}

void RecipeList::display_recipe_list() {
    for(const auto& pair : recipes)
    {
        int key = pair.first;
        std::string name = pair.second.get_title();

        // display all the recipes with a number to call them with (key)
        std::cout << key << ": " << name << std::endl;
    }
}

std::map<int, Recipe> RecipeList::get_recipe_list() {return recipes;}
