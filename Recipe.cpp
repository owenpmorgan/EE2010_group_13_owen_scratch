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

// get the amount a recipe needs of a SPECIFIC ingredient, via it's uuid
//std::optional<int> Recipe::get_amount(int uuid){
//
//    //
//    auto it = recipe_ingredients.find(uuid);
//    // if the uuid of the inredient is in recipe ingredients, and its type is generic or 'to taste' just return 0 - maybe late fix this
//    if (it != recipe_ingredients.end() && get_ingredient(uuid).get_measurement_type() == MeasurementType::GENERIC) {
//        return std::nullopt;
//    }
//    // otherwise, normal ingredient, return the second element of the unordered map, the amount.
//    else {
//        return it->second;
//    }
//}

std::unordered_map<int, std::optional<int>> Recipe::get_recipe_ingredients() const {return recipe_ingredients;}

void Recipe::display_recipe_ingredients(std::unordered_map<int, Ingredient> ingredients_list) const
{
    std::cout << "Ingredients for " << title << ":\n";
    // iterate over the ingredients needed for the recipe, the current iteration is called ingredient
    for(const auto& ingredient : recipe_ingredients)
    {
        // scan the master ingredients list for ingredients in the recipe
        // it = the item on master ingredients list with at the first value of local iteration 'ingredient', which is the uuid
        auto it = ingredients_list.find(ingredient.first);
        //the second value of ingredient is from recipe_ingredients, and is the amount, check it's a countable value
        if(ingredient.second.has_value()){
            // the second value of it (the iterator) is the Ingredient object, the second value of ingredient is the amount
            std::cout << it->second.get_name() << ": " << ingredient.second.value() << " " << it->second.get_unit() << std::endl;
        }
        else{
            std::cout << it->second.get_name() << ": " << "to taste" << std::endl;

        }
    }
}