//
// Created by Owen Morgan on 26/11/2024.
//

#include "RecipeList.h"
#include <iomanip>

void RecipeList::add_recipe_to_list(const Recipe& recipe)
{
    recipes[next_id] = recipe;
    next_id++;
}

Recipe& RecipeList::get_recipe_by_id(int id)
{
    if (recipes.find(id) == recipes.end()) {
        throw std::runtime_error("Recipe with ID " + std::to_string(id) + " not found.");
    }
    return recipes[id];
}

void RecipeList::display_recipe_list() {

    int col_count = 0;
    int col_width = 60;

    for(const auto& pair : recipes)
    {
        int key = pair.first;
        std::string name = pair.second.get_title();

        // display all the recipes with a number to call them with (key)
        std::cout << std::left << std::setw(3) << key << ": " << std::setw(col_width) << name;
        col_count++;
        if(col_count > 2)
        {
            std::cout << "\n";
            col_count = 0;
        }
    }
}

std::map<int, Recipe>& RecipeList::get_recipe_list() {return recipes;}
