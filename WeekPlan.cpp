//
// Created by Owen Morgan on 08/11/2024.
//

#include "WeekPlan.h"
#include "Recipe.h"

WeekPlan::WeekPlan() {

    for(auto& it : weeks_recipes)
    {
        it = Recipe("No Recipe", 0);
    }

}
//  provide a recipe name from the list and which meal of the 21 per week you want to assign it to
void WeekPlan::add_recipe(const Recipe& recipe_to_add) {

    int serving = 1;
    int user_choice = -1;

    // on adding a recipe cycle through it's ingredients and add them to the total ingredients necessary for the week
    const auto &recipe_ingredients = recipe_to_add.get_recipe_ingredients();

//    this sums the total ingredients for the added recipe
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
                // if it exists, make sure it is nullopt
                total_ingredients[uuid] = std::nullopt;
            } else
            {
                // if it doesn't exist, add a new entry that's nullopt
                total_ingredients[uuid] = std::nullopt;
            }
        }
    }


    //nOw distribute the number of portions the recipe makes over the week
    std::cout << recipe_to_add.get_title() << " makes " << recipe_to_add.get_portions() << " portions." << std::endl;

    while(serving <= recipe_to_add.get_portions())
    {

        // todo make this a function in the organiser which sanitises the input

        while(true)
        {
            std::cout << "Where would you like to put serving " << serving << std::endl;
            std::cin >> user_choice;
            if (weeks_recipes[user_choice - 1].get_title() == "No Recipe")
            {
                weeks_recipes[user_choice - 1] = recipe_to_add;
                break;
            }
            else if(user_choice < 1 || user_choice > MAX_RECIPES)
            {
                std::cout << "Please enter a number between 0 & " << MAX_RECIPES << std::endl;
            }
            else
            {
                std::cout << "There is already a recipe in that slot" << std::endl;
                display_weeks_recipes();
            }
        }

        serving++;
    }
}

// display the currently selected weekly plan of meals
void WeekPlan::display_weeks_recipes() const {
    std::cout << "Recipes in the WeekPlan:" << std::endl;

    std::cout   << "Monday\t\t\t\t"
                << "Tuesday\t\t\t\t"
                << "Wednesday\t\t\t\t"
                << "Thursday\t\t\t\t"
                << "Friday\t\t\t\t"
                << "Saturday\t\t\t\t"
                <<  "Sunday\t\t\t\t"
                << std::endl;
    // Outer loop to handle each row
    for (int row = 0; row < 3; row++) {
        // Inner loop to print every 7th entry starting at the offset given by 'row'
        for (int col = 0; col < 7; col++) {
            int index = row + col * 3;
            if (index < MAX_RECIPES) {  // Ensure we don't go out of bounds
                std::cout << index + 1 << "- " << weeks_recipes[index].get_title() << "\t\t\t\t";
            }
        }
        std::cout << std::endl;  // Newline after each row
    }
}

// this just returned the total ingredients list after it has been summed, in case we need to use the list somewhere else.
// eg to a shopping list class that formats it as checkboxes etc.
std::unordered_map<int, std::optional<int>> WeekPlan::get_total_ingredients() {return total_ingredients;}

// display the total_ingredients member variable
void WeekPlan::display_total_weeks_ingredients(std::unordered_map<int, Ingredient> ingredients_list) {
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
}