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
    // unordered map of uuid (key) amount (value)
    std::unordered_map<int, int> total_ingredients;

public:

    WeekPlan();
    ~ WeekPlan() = default;

    virtual int get_int_input() override;

    void add_recipe(const Recipe&);

    std::unordered_map<int, int> get_total_ingredients();

    void sum_total_weeks_ingredients();
    void display_weeks_recipes() const;
    void display_total_weeks_ingredients(std::unordered_map<int, Ingredient>);


};

#endif //EE2010_GROUP_MY_SCRATCH_WEEKPLAN_H
