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
//  Provide the number of a recipe index, and take a pointer to the master recipe list
void WeekPlan::add_recipe(int recipe_to_add, std::map<int, Recipe>* recipe_list) {

    // make a temporary emtpy recipe to be the working recipe
    Recipe current_recipe;

    // find the recipe of the given recipe index in the recipe list, and update current recipe to be that recipe
    if(recipe_list->find(recipe_to_add) != recipe_list->end())
    {
        current_recipe = recipe_list->at(recipe_to_add);
    }
    else
    {
        throw std::runtime_error("WEEKPLAN: Recipe index not found");
    }

    // get_recipe_ingredients returns an unordered map<uuid:int, amount:int>
    const auto& recipe_ingredients = current_recipe.get_recipe_ingredients();

    // iterate through the recipe ingredients unordered_map, the iterator (called ingredient) is a pointer to one of the ingredients
    for (const auto &ingredient: recipe_ingredients)
    {
        // store the value of the uuid of the current ingredient being iterated thorugh
        int uuid = ingredient.first;
        // store the second value of the current ingredient in an optional in called ammount
        int amount = ingredient.second;

        // -1 is a sentinel value, used in the parser to mean the ingredient amount is non-numeric (eg, "to taste")
        // if amount is numerical...
        if (amount != -1)
        {
            // If the ingredient UUID is already in the total_ingredients for the week list, add the new amount
            if (total_ingredients.find(uuid) != total_ingredients.end())
            {
                total_ingredients[uuid] = total_ingredients[uuid] + amount;
            }
                // otherwise make a new entry in the total_ingredients list
            else
            {
                total_ingredients[uuid] = amount;
            }
        }
            // if amount is NOT numerical
        else
        {
            // do the same but just apply the sentinel value
            if (total_ingredients.find(uuid) != total_ingredients.end())
            {
                // if the uncountable item, eg "pepper" is on the list already ignore
                break;
            } else
            {
                // if it doesn't exist, add a new entry that has the non countable sentinel value
                total_ingredients[uuid] = -1;
            }
        }
    }

    // once summed, dispaly the week_plan
    display_weeks_recipes();

    // Now get the user to say where to place the recipe
    std::cout << "Recipe to add: " << current_recipe.get_title() << std::endl;

    while(true)
    {
        int user_choice = get_int_input();

        // if the user_choice selects an empty slot in the weeks_recipes array, add the current recipe
        if (weeks_recipes[user_choice - 1].get_title() == "No Recipe")
        {
            weeks_recipes[user_choice - 1] = current_recipe;
            break;
        }
        // otherwise warn they have aleady filled this slot
        else
        {
            std::cout << "There is already a recipe in that slot" << std::endl;
            // displays recipes again to allow user to see the available slots
            display_weeks_recipes();
        }
    }

}

void WeekPlan::delete_meal_from_plan() {

    std::cout << "Which meal would you like to delete?" << "\n";

    // weeks recipes starts at 1, but the array starts at 0 so deduct 1
    int user_choice = get_int_input() - 1;

    // get the recipe to delete in the weeks_recipes array
    Recipe& recipe_to_delete = weeks_recipes[user_choice];

    // if the user chose an empty slot, warn them and return
    if(weeks_recipes[user_choice].get_title() == "No Recipe")
    {
        std::cout << "There is no recipe in that slot\n";
        return;
    }


    // otherwise, this is the the same ass adding recipe ingredient amounts but, now it deducts
    // iterator to cycle through the ingredients for the recipe in the selected slot
    const auto& recipe_ingredients = recipe_to_delete.get_recipe_ingredients();

    //  iterate over ingredients one by one, note; pair will be <int(uuid), int(amount)>
    for (const auto &ingredient: recipe_ingredients)
    {
        // get uuid and amount of current ingredient in recipe
        int uuid = ingredient.first;
        int amount = ingredient.second;

        // if it can find the ingredients uuid in the total_ingredient list already..
        if (total_ingredients.find(uuid) != total_ingredients.end())
        {
            // deduct the amount of the ingredient needed for the recipe to be deleted
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

int WeekPlan::get_int_input(int min, int max)
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
            if(!(std::cin >> userChoice) || userChoice < min || userChoice > max)
            {
                // clear the error flag and buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // make the error string
                std::stringstream error_string;
                error_string << "Invalid input. Please enter a number between " << min << " and " << max << ".";

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
    std::cout << "WeekPlan:" << std::endl;

    // display spaces value to be used below
    const int spaces = 30;

    // an array of strings for the day names
    const std::string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // for each day, count through the available spaces (up to the max) and either print a character of the days name
    // or a space if the days name has been completed
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
    std::cout << std::endl;  // Newline after complete table
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

        // for each ingredient iterated over, make an iterator that grabs the ingredient with the same UUDI as our
        // temporary ingredient from the ingredients list
        auto it = ingredients_list->find(ingredient.first);

        // this if makes sure the ingredient was found
        if (it != ingredients_list->end())
        {
            // if that ingredients amount (.second) field is not the sentinel value
            if (ingredient.second != -1)
            {
                // print it along with the amount
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
    std::cout << std::endl;
}

std::unordered_map<int, int> WeekPlan::get_total_ingredients(){return total_ingredients;}