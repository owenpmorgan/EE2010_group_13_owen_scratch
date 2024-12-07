//
// Created by Owen Morgan on 05/11/2024.
//

#ifndef EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H
#define EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H

#include "Organiser.h"
#include "Ingredient.h"

// Inherit from organiser class
class IngredientList
{

private:
    std::unordered_map<int, Ingredient> ingredients_list;

public:

    // No need for implemented constructor here, constructed one by one in json parsing
    IngredientList();
    // destructor
    ~IngredientList() = default;

    void add_ingredient(const Ingredient& ingredient);

    // Not used in this version but useful to have for future development
    void display_total_ingredients_list() const;
    Ingredient get_ingredient(int uuid);

    std::unordered_map<int, Ingredient>& get_ingredients_list();

};


#endif //EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H
