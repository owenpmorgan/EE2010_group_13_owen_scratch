//
// Created by Owen Morgan on 05/11/2024.
//

#include "Recipe.h"

#include <optional>

Recipe::Recipe(std::string title)
              : title(title)
{
}

void Recipe::add_ingredient(const int uuid, int amount)
{
    auto result = recipe_ingredients.insert({uuid, amount});
    if (!result.second)
    {
        throw std::runtime_error("Ingredient with this UUID already exists.");
    }
}


std::string Recipe::get_title() const{
    return title;
}

std::unordered_map<int, int> Recipe::get_recipe_ingredients() const {return recipe_ingredients;}

void Recipe::display_recipe_ingredients(std::unordered_map<int, Ingredient> ingredients_list) const
{
    std::cout << "Ingredients for " << title << ":\n";
    // iterate over the ingredients needed for the recipe, the current iteration is called ingredient, and recipe ingredients
    // are key/value pairs <uuid, amount>
    for(const auto& ingredient : recipe_ingredients)
    {
        // find the ingredient on the ingredients list of the local variable ingredient 's first value, it's uuid
        auto it = ingredients_list.find(ingredient.first);

        if(ingredient.second != -1){

            std::cout << it->second.get_name() << ": " << ingredient.second << " " << it->second.get_unit() << std::endl;
        }
        else{
            std::cout << it->second.get_name() << ": " << "to taste" << std::endl;

        }
    }
}