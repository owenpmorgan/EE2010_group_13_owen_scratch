//
// Created by Owen Morgan on 08/11/2024.
//

#include "WeekPlan.h"
#include "Recipe.h"


void WeekPlan::add_recipe(const Recipe& recipe, int index) {

    if (index < MAX_RECIPES && index > 0) {
        weeks_recipes[index-1] = recipe;
    } else {
        throw std::runtime_error("Please enter meal number from 1-21");
    }
}

void WeekPlan::display_weeks_recipes() const {
    std::cout << "Recipes in the WeekPlan:" << std::endl;
    for (int i = 0; i < MAX_RECIPES; ++i)
    {
        std::cout << i+1 <<"- " << weeks_recipes[i].get_title() << std::endl;
    }
}

void WeekPlan::get_ingredients_for_index(int index){
    weeks_recipes[index-1].display_recipe_ingredients();
}

void WeekPlan::sum_total_ingredients() {
    for (int i = 0; i < MAX_RECIPES; ++i)
    {
        const auto &recipe_ingredients = weeks_recipes[i].get_recipe_ingredients();

        for (const auto &ingredient: recipe_ingredients)
        {
            int uuid = ingredient.first;
            int amount = ingredient.second;

            if (total_ingredients.find(uuid) != total_ingredients.end())
            {
                total_ingredients[uuid] += amount;
            } else
            {
                total_ingredients[uuid] = amount;
            }
        }

    }
}

std::unordered_map<int, int> WeekPlan::get_total_ingredients() {return total_ingredients;};

void WeekPlan::display_total_ingredients(){
    // Display the total ingredients
    std::cout << "Total Ingredients for the Week Plan:" << std::endl;
    for (const auto &ingredient: total_ingredients)
    {

        auto it = ingredients_list.find(ingredient.first);
        if (it != ingredients_list.end())
        {

            std::cout << "- " << it->second.get_name() << ": " << ingredient.second << " " << it->second.get_unit()
                      << std::endl;
        } else
        {
            std::cout << "- Unknown ingredient with UUID " << ingredient.first << ": " << ingredient.second
                      << " units" << std::endl;
        }
    }
};