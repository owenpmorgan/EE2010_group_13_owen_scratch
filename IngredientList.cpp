//
// Created by Owen Morgan on 05/11/2024.
//

#include "IngredientList.h"
#include "Ingredient.h"

// a function of ingredient list to add an ingredient, it takes the new ingredient only
void IngredientList::add_ingredient(const Ingredient& ingredient) {

    auto result = ingredients_list.insert({ingredient.get_uuid(), ingredient});
    if (!result.second) {
        throw std::runtime_error("Ingredient with this UUID already exists.");
    }
}

int IngredientList::get_int_input() {return -1;}

// function for retrieving an ingredient from the list by UUID
Ingredient IngredientList::get_ingredient(int uuid) {

    if (ingredients_list.find(uuid) != ingredients_list.end()) {
        return ingredients_list.at(uuid);
    } else {
        throw std::out_of_range("Ingredient with the specified UUID not found.");
    }
}

// function for displaying all currently stored ingredients
void IngredientList::display_total_ingredients_list() const
{
    for(const auto& pair : ingredients_list)
    {
        pair.second.display();
    }
}

std::unordered_map<int, Ingredient> IngredientList::get_ingredients_list() {return ingredients_list;}