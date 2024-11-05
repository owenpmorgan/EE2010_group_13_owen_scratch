//
// Created by Owen Morgan on 05/11/2024.
//

#ifndef EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H
#define EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H

#include "Ingredient.h"

class IngredientList
{
public:
    static void add_ingredient(const Ingredient& ingredient);
    static Ingredient get_ingredient(int uuid);
    void display_total_ingredients_list() const;

private:
    static std::unordered_map<int, Ingredient> ingredients_list;
};


#endif //EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H
