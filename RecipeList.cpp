//
// Created by Owen Morgan on 26/11/2024.
//

#include "RecipeList.h"
#include <iomanip>

// Add recipe to list along with an enumerator to allow easy selction
void RecipeList::add_recipe_to_list(const Recipe& recipe)
{
    recipes[next_id] = recipe;
    next_id++;
}

// Used to get the recipe at a specified id (key value in the map)
Recipe& RecipeList::get_recipe_by_id(int id)
{
    // throw an error if the requested ID doesn't exist
    if (recipes.find(id) == recipes.end())
    {
        throw std::runtime_error("Recipe with ID " + std::to_string(id) + " not found.");
    }

    return recipes[id];
}

void RecipeList::display_recipe_list() {

    // counter to make 3 columns
    int col_count = 0;
    int num_cols = 2;
    int col_width = 60;

    // go through recipes and retrieve each key value pair
    for(const auto& pair : recipes)
    {
        // grab the pair and save them each to a local variable
        int key = pair.first;
        std::string name = pair.second.get_title();

        // display all the recipes in a line
        std::cout << std::left << std::setw(3) << key << ": " << std::setw(col_width) << name;
        col_count++;
        if(col_count > num_cols)
        {
            std::cout << "\n";
            col_count = 0;
        }
    }
    std::cout << std::endl;
}

std::map<int, Recipe>& RecipeList::get_recipe_list() {return recipes;}
