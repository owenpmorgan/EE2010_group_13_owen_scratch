//
// Created by Owen Morgan on 05/11/2024.
//

#include "IngredientList.h"
#include "Ingredient.h"

//std::unordered_map<int, Ingredient> IngredientList::ingredients_list;

// a function of ingredient list to add an ingredient, it takes the new ingredient only
void IngredientList::add_ingredient(const Ingredient& ingredient) {

    // insert the new ingredient to ingredients_list, giving a key, its uuid, and then the value 'ingredient object',
    // capture the result as an auto variable, which captures result.first as the unordered map object
    // <unordered_map<int, ingredient>> second as a bool of whether the insertion was successful. This is an insert
    // command standard, insert returns first the value inserted, and second whether it happened.
    auto result = ingredients_list.insert({ingredient.get_uuid(), ingredient});
    // if the bool, second result DIDN't happen then it must have been becasue the uuid already exists, so throw an error
    if (!result.second) {
        throw std::runtime_error("Ingredient with this UUID already exists.");
    }
}

// function for retrieving an ingredient from the list by UUID
Ingredient IngredientList::get_ingredient(int uuid) {
    // Look for the uuid until the end, if not found it will hit end
    if (ingredients_list.find(uuid) != ingredients_list.end()) {
        // if found, return where it is, this returns the ingredient at the point, not the index
        return ingredients_list.at(uuid);
    } else {
        // if not found throw an error
        throw std::out_of_range("Ingredient with the specified UUID not found.");
    }
}

// function for displaying all currently stored ingredients
void IngredientList::display_total_ingredients_list() const
{
    // ingredients list is a unorderd list, that works with pairs
    for(const auto& pair : ingredients_list)
    {
        // the second pair is the ingredient object, and it has a display function we can call
        pair.second.display();
    }
}

std::unordered_map<int, Ingredient> IngredientList::get_ingredients_list() {return ingredients_list;}