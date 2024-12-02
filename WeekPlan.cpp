//
// Created by Owen Morgan on 08/11/2024.
//

#include <iostream>

#include "WeekPlan.h"
#include "Recipe.h"

WeekPlan::WeekPlan() {

    for(auto& it : weeks_recipes)
    {
        it = Recipe("No Recipe", 0, "");
    }

}



void WeekPlan::clear_week_plan()
{
    for(auto& it : weeks_recipes)
    {
        it = Recipe("No Recipe", 0, "");
    }

    total_ingredients.clear();

}
//  provide a recipe name from the list and which meal of the 21 per week you want to assign it to
void WeekPlan::add_recipe(int recipe_to_add, std::map<int, Recipe>* recipe_list) {

    Recipe current_recipe;

    if(recipe_list->find(recipe_to_add) != recipe_list->end())
    {
        current_recipe = recipe_list->at(recipe_to_add);
    }
    else
    {
        throw std::runtime_error("WEEKPLAN: Recipe index not found");
    }

    // get recipe ingredients is an unordered map<uuid:int, amount:int>
    const auto& recipe_ingredients = current_recipe.get_recipe_ingredients();

//    std::cout << "Number of ingredients in recipe: " << recipe_ingredients.size() << "\n";
//    std::cout << "Recipe Title: " << current_recipe.get_title() << "\n";

//    this sums the total ingredients for the added recipe
    for (const auto &ingredient: recipe_ingredients)
    {
        // grab the uuid of this ingredient to compare it to the list of total ingredients and see where it is or if
        // it has not been added yet
        int uuid = ingredient.first;
        // store the second value of the current ingredient in an optional in called ammount
        int amount = ingredient.second;

//        std::cout << "Ingredient UUID: " << uuid << ", Amount: " << amount << "\n";

        // if amount is numerical...
        if (amount != -1)
        {
            // if it can find the ingredients uuid in the total_ingredient list already, sum the amounts
            if (total_ingredients.find(uuid) != total_ingredients.end())
            {
                total_ingredients[uuid] = total_ingredients[uuid] + amount;
            }
                // otherwise make a new entry
            else
            {
                total_ingredients[uuid] = amount;
            }
        }
            // if amount is NOT numerical
        else
        {
            // do the same but just apply the null value
            if (total_ingredients.find(uuid) != total_ingredients.end())
            {
                // if it exists, make sure it is the unused sentinel value
                total_ingredients[uuid] = -1;
            } else
            {
                // if it doesn't exist, add a new entry that has the non countable sentinel value
                total_ingredients[uuid] = -1;
            }
        }
    }

    // add comments
    display_weeks_recipes();

    std::cout << "Recipe to add: " << current_recipe.get_title() << std::endl;

    while(true)
    {
        int user_choice = get_int_input();

        if (weeks_recipes[user_choice - 1].get_title() == "No Recipe")
        {
            weeks_recipes[user_choice - 1] = current_recipe;
            break;
        }
        else
        {
            std::cout << "There is already a recipe in that slot" << std::endl;
            display_weeks_recipes();
        }
    }

}

void WeekPlan::delete_meal_from_plan() {

    std::cout << "Which meal would you like to delete?" << "\n";

    // weeks recipes starts at 1, but the array starts at 0 so deduct 1
    int user_choice = get_int_input() - 1;

    Recipe& recipe_to_delete = weeks_recipes[user_choice];

    if(weeks_recipes[user_choice].get_title() == "No Recipe")
    {
        std::cout << "There is no recipe in that slot\n";
        return;
    }


    // iterator to cycle through the ingredients for the recipe in the selected slot
    const auto& recipe_ingredients = recipe_to_delete.get_recipe_ingredients();

//  go through the ingredients one by one, note pair will be <int, uuid, int amount>
    for (const auto &ingredient: recipe_ingredients)
    {
        // grab the uuid of this ingredient to compare it to the list of total ingredients and see where it is or if
        // it has not been added yet
        int uuid = ingredient.first;
        // store the second value of the current ingredient in an optional in called ammount
        int amount = ingredient.second;

        // debug line
//        std::cout << "Ingredient UUID: " << uuid << ", Amount: " << amount << "\n";

        // if it can find the ingredients uuid in the total_ingredient list already, sum the amounts
        if (total_ingredients.find(uuid) != total_ingredients.end())
        {
            total_ingredients[uuid] = total_ingredients[uuid] - amount;
        }
        else
        {
            throw std::runtime_error("WEEKPLAN: item to delete not found in total ingredients list");
        }
        // if this results in a zero value for an ingredient in the weekly list, delete, note do NOT do < 1,
        // because all the sentinal values for uncountable ingredients are -1, and they would be erased too even if they
        // were used in other recipes.
        if (total_ingredients[uuid] == 0)
        {
            total_ingredients.erase(uuid);
        }
    }

    // reset the recipe in that slot
    weeks_recipes[user_choice] = Recipe("No Recipe", 0, "");

}

int WeekPlan::get_int_input()
{
    // the int to be returned
    int userChoice;

    // redefine get int input from parent class organiser to make it specific to choosing a meal slot in the weekplan
    std::cout << "Enter the number of the meal slot: ";

    // While not a valid entry clear cin and try again
    while(true)
    {
        try
        {
            // if cin is not given as the correct data type for userChoice, int, cin returns a false
            // if the data type IS an int, but is out of bounds run this code as well
            if(!(std::cin >> userChoice) || userChoice < 1 || userChoice > MAX_RECIPES)
            {
                // clear the error flag and buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // make the error string
                std::stringstream error_string;
                error_string << "Invalid input. Please enter a number between 1 and " << MAX_RECIPES << ".";

                throw std::runtime_error(error_string.str());
            }
            // if input valid, break the while loop
            break;
        }
        // send an error, which is the error string constructed above
        catch (const std::runtime_error& error)
        {
            std::cout << error.what() << std::endl;
        }
    }
    return userChoice;
}

// display the currently selected weekly plan of meals
void WeekPlan::display_weeks_recipes() const {
    std::cout << "Recipes in the WeekPlan:" << std::endl;

    const int spaces = 30;
    const std::string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    for (const auto &day: days) {
        for (int i = 0; i < spaces; i++) {
            if (day.size() > i) {
                std::cout << day[i];
            } else {
                std::cout << " ";
            }
        }

    }
    std::cout << std::endl;

    // std::cout   << "Monday" <<
    //             << "Tuesday\t\t\t\t"
    //             << "Wednesday\t\t\t\t"
    //             << "Thursday\t\t\t\t"
    //             << "Friday\t\t\t\t"
    //             << "Saturday\t\t\t\t"
    //             <<  "Sunday\t\t\t\t"
    //             << std::endl;


    // Outer loop to handle each row
    for (int row = 0; row < 3; row++) {
        // Inner loop to print every 7th entry starting at the offset given by 'row'
        for (int col = 0; col < 7; col++) {
            int index = row + col * 3;
            if (index < MAX_RECIPES) {  // Ensure we don't go out of bounds
                std::cout << index+1 << ": ";
                int spaces_left = spaces - 3;
                if (index+1 > 9) spaces_left -= 1;
                // Print only first 20 characters of string or fill with empty space up to 20 chars
                for (int i = 0; i < spaces_left; i++) {
                    if (weeks_recipes[index].get_title().size() > i) {
                        std::cout << weeks_recipes[index].get_title()[i];
                    } else {
                        std::cout << " ";
                    }
                }
                // std::cout << index + 1 << "- " << weeks_recipes[index].get_title() << "\t\t\t\t";
            }
        }
        std::cout << std::endl;  // Newline after each row
    }
}

// DEBUG this just returnes the total ingredients list after it has been summed, in case we need to use the list somewhere else.
//std::unordered_map<int, std::optional<int>> WeekPlan::get_total_ingredients() {return total_ingredients;}

// display the total_ingredients member variable
void WeekPlan::display_shopping_list(std::unordered_map<int, Ingredient>* ingredients_list) {
    // Display the total ingredients
    std::cout << "Your shopping list for this week plan:" << std::endl;
    // new temp variable ingredient loops over total ingredients, it's value will be a key value pair (uuid, amount)
    for (const auto ingredient: total_ingredients)
    {

        // this iterator goes over the master ingredient list in the ingredient list class until it finds the uuid (first)
        // of the temp ingredient variable, it then stores this as a pointer to the unordered_map ingredient list where it
        // found the key value, so the first field is the uuid and the second field the ingredient object
        auto it = ingredients_list->find(ingredient.first);

        // if it didn't find it, it would just store the marker for the end of the ingredentList
        if (it != ingredients_list->end())
        {
            // if the 'amount' field is not nullopt, and is an integer value
            if (ingredient.second != -1)
            {
                // ingredient is just (uuid, amount), to get the name we need to use the iterator which points to an
                // Ingredient type and use the get_name member function of Ingredient.
                std::cout << "- " << it->second.get_name() << ": " << ingredient.second << " " << it->second.get_unit()
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

std::unordered_map<int, int> WeekPlan::get_total_ingredients(){return total_ingredients;}