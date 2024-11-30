//
// Created by Owen Morgan on 05/11/2024.
//

#ifndef EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H
#define EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H

#include "Organiser.h"
#include "Ingredient.h"

class IngredientList : public Organiser
{
    // todo maybe instead use a get ingredient list rather than opening up the whole list
private:
    std::unordered_map<int, Ingredient> ingredients_list;

public:

    // No need for constructor here, constructed one by one in json parsing
    IngredientList();
    // destructor
    ~IngredientList() = default;

    virtual int get_int_input() override;

    void add_ingredient(const Ingredient& ingredient);
    void display_total_ingredients_list() const;

    Ingredient get_ingredient(int uuid);
    std::unordered_map<int, Ingredient> get_ingredients_list();

};


#endif //EE2010_GROUP_MY_SCRATCH_INGREDIENTLIST_H
