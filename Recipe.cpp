//
// Created by Owen Morgan on 05/11/2024.
//

#include "Recipe.h"
#include "IngredientList.h"
#include "MeasurementType.h"

Recipe::Recipe(std::string title)
              : title(title)
{
}

void Recipe::add_ingredient(const int uuid, int amount)
{
    // insert the new ingredient to ingredients_list, giving a key, its uuid, and then the value 'ingredient object',
    // capture the result as an auto variable, which captures result.first as the unordered map object
    // <unordered_map<int, ingredient>> second as a bool of whether the insertion was successful. This is an insert
    // command standard, insert returns first the value inserted, and second whether it happened.
    auto result = recipe_ingredients.insert({uuid, amount});
    // if the bool, second result DIDN't happen then it must have been becasue the uuid already exists, so throw an error
    if (!result.second)
    {
        throw std::runtime_error("Ingredient with this UUID already exists.");
    }
}

std::string Recipe::get_title() const{
    return title;
}

int Recipe::get_amount(int uuid){

    auto it = recipe_ingredients.find(uuid);
    // if the uuid of the inredient is in recipe ingredients, and its type is generic or 'to taste' just return 0 - maybe late fix this
    if (it != recipe_ingredients.end() && get_ingredient(it->second).get_measurement_type() == MeasurementType::GENERIC) {
        return 0;
    }
    // otherwise, normal ingredient, return the second element of the unordered map, the amount.
    else {
        return it->second;
    }
}

std::unordered_map<int, int> Recipe::get_recipe_ingredients() {return recipe_ingredients;}

void Recipe::display_recipe_ingredients() const
{
    std::cout << "Ingredients for " << title << ":\n";
    for(const auto& ingredient : recipe_ingredients)
    {
        // it = the item on ingredients list with at the first value of 'ingredient', that is the uuid
        auto it = ingredients_list.find(ingredient.first);
        // the second value of it is the Ingredient object, the second value of ingredient is the amount
        std::cout << it->second.get_name() << ": " << ingredient.second << " " << it->second.get_unit() << std::endl;
    }
}