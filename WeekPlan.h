//
// Created by Owen Morgan on 08/11/2024.
//

#include "Recipe.h"

#ifndef EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H
#define EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H


class WeekPlan : public Organiser
{

private:

    Recipe weeks_recipes[MAX_RECIPES];
    std::unordered_map<int, std::optional<int>> total_ingredients;

public:
    // Add a recipe and the index, from 0-21 of when that meal will come
    void add_recipe(const Recipe&);

//    void get_ingredients_for_index(int); // I dont think needed

    std::unordered_map<int, std::optional<int>> get_total_ingredients();

    void sum_total_weeks_ingredients();
    void display_weeks_recipes() const;
    void display_total_weeks_ingredients(std::unordered_map<int, Ingredient>);

};

#endif //EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H
