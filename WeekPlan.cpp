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
        // New variable recipe Ingredients = the meal at the current index we have got to in the iteration, which
        // returns it's unordered map list of ingredients (uuid, amount)
        const auto &recipe_ingredients = weeks_recipes[i].get_recipe_ingredients();

        // now for loop through this unordered map of ingredients, each iteration the variable imgredient will be updated
        for (const auto &ingredient: recipe_ingredients)
        {
            // grab the uuid of this ingredient to compare it to the list of total ingredients and see where it is or if
            // it has not been added yet
            int uuid = ingredient.first;
            // and grab the amount, being sure it can also receive nullopt

            // store the second value of the current ingredient in an optional in called ammount
            std::optional<int> amount = ingredient.second;
            // if amount is numerical...
            if (amount.has_value())
            {
                // if it can find the ingredients uuid in the total_ingredient list already, sum the amounts
                if (total_ingredients.find(uuid) != total_ingredients.end())
                {
                    total_ingredients[uuid] = total_ingredients[uuid].value() + amount.value();
                }
                // otherwise make a new entry
                else
                {
                    total_ingredients[uuid] = amount.value();
                }
            }
            // if amount is NOT numerical
            else
            {
                // do the same but just apply the null value
                if (total_ingredients.find(uuid) != total_ingredients.end())
                {
                    total_ingredients[uuid] = std::nullopt;
                }
                else
                {
                    total_ingredients[uuid] = std::nullopt;
                }
            }
        }
    }
}

std::unordered_map<int, std::optional<int>> WeekPlan::get_total_ingredients() {return total_ingredients;};

void WeekPlan::display_total_ingredients(){
    // Display the total ingredients
    std::cout << "Total Ingredients for the Week Plan:" << std::endl;
    // new temp variable ingredient loops over total ingredients, it's value will be a key value pair (uuid, amount)
    for (const auto ingredient: total_ingredients)
    {
        // this iterator goes over the master ingredient list in the ingredient list class until it finds the uuid (first)
        // of the temp ingredient variable, it then stores this as a pointer to the unordered_map ingredient list where it
        // found the key value, so the first field is the uuid and the second field the ingredient object
        auto it = ingredients_list.find(ingredient.first);

        // if it didn't find it, it would just store the marker for the end of the ingredentList
        if (it != ingredients_list.end())
        {
            // if the 'amount' field is not nullopt, and is an integer value
            if (ingredient.second.has_value())
            {
                // ingredient is just (uuid, amount), to get the name we need to use the iterator which points to an
                // Ingredient type and use the get_name member function of Ingredient.
                std::cout << "- " << it->second.get_name() << ": " << ingredient.second.value() << " " << it->second.get_unit()
                          << std::endl;
            }
            // if it DOESNT have a value associated just print the name
            else
            {
                std::cout << "- " << it->second.get_name() << std::endl;
            }
        }

    }
};