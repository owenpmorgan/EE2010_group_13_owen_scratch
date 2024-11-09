//
// Created by Owen Morgan on 08/11/2024.
//

#include "Recipe.h"

#ifndef EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H
#define EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H


class WeekPlan : public IngredientList
{

private:
    static const int MAX_RECIPES = 21;  // Fixed size of 21
    Recipe weeks_recipes[MAX_RECIPES];
    std::unordered_map<int, int> total_ingredients;

public:
    // Add a recipe and the index, from 0-21 of when that meal will come
    void add_recipe(const Recipe&, int);
    void display_weeks_recipes() const;
    void get_ingredients_for_index(int);
    void sum_total_ingredients();
    std::unordered_map<int, int> get_total_ingredients();
    void display_total_ingredients();


};


#endif //EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H
