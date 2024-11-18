//
// Created by Owen Morgan on 05/11/2024.
//

#include "Recipe.h"

#include <optional>

Recipe::Recipe(std::string title, int portions)
              : title(title), portions(portions)
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

// the same but support being able to make one without an amount for herbs etc.
void Recipe::add_ingredient(const int uuid) {
    auto result = recipe_ingredients.insert({uuid, std::nullopt});
    // if the bool, second result DIDN't happen then it must have been becasue the uuid already exists, so throw an error
    if (!result.second)
    {
        throw std::runtime_error("Ingredient with this UUID already exists.");
    }
}

std::string Recipe::get_title() const{
    return title;
}

int Recipe::get_portions() const {return portions;}

std::unordered_map<int, std::optional<int>> Recipe::get_recipe_ingredients() const {return recipe_ingredients;}

void Recipe::display_recipe_ingredients(std::unordered_map<int, Ingredient> ingredients_list) const
{
    std::cout << "Ingredients for " << title << ":\n";
    // iterate over the ingredients needed for the recipe, the current iteration is called ingredient
    for(const auto& ingredient : recipe_ingredients)
    {
        auto it = ingredients_list.find(ingredient.first);

        if(ingredient.second.has_value()){

            std::cout << it->second.get_name() << ": " << ingredient.second.value() << " " << it->second.get_unit() << std::endl;
        }
        else{
            std::cout << it->second.get_name() << ": " << "to taste" << std::endl;

        }
    }
}