//
// Created by Owen Morgan on 08/11/2024.
//

#include "Recipe.h"
#include <map>

#ifndef EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H
#define EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H


class WeekPlan : public Organiser
{

private:

    // unordered map of uuid (key) amount (value)
    std::unordered_map<int, int> total_ingredients;
    Recipe weeks_recipes[MAX_RECIPES];

public:

    WeekPlan();
    ~ WeekPlan() = default;

    virtual int get_int_input() override;

    void add_recipe(int, std::map<int, Recipe>*);
    void display_weeks_recipes() const;
    void display_shopping_list(std::unordered_map<int, Ingredient>*);
    std::unordered_map<int, int> get_total_ingredients();
    void clear_week_plan();
    void delete_meal_from_plan();

//    void sum_total_weeks_ingredients();

};

#endif //EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H
