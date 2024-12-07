//
// Created by Owen Morgan on 05/11/2024.
//

#include "Recipe.h"

#include <optional>

Recipe::Recipe(std::string title, int portions, std::string method)
              : title(title),
              portions(portions),
              method(method)
{
}

// used to populate a newly created recipe with the ingredients needed to make it
void Recipe::add_ingredient(const int uuid, int amount)
{
    // try to insert the ingredient
    auto result = recipe_ingredients.insert({uuid, amount});
    // result.second is a bool that is set false if fails. If so there is given UUID already in list, so throw and error
    if (!result.second)
    {
        throw std::runtime_error("RECIPE: Ingredient with this UUID already exists.");
    }
}


std::string Recipe::get_title() const{
    return title;
}

std::string Recipe::get_recipe_method() const {return method;}

void Recipe::display_recipe_method() const
{
    // max line length for display
    int line_length = 150;
    // counter to check current line length
    int counter = 0;
    // enumerate distinct steps in the recipe (recipe method is an array of strings representing steps
    int step_enumerator = 1;

    // Start a step
    std::cout << step_enumerator << ": ";

    // loop over each char in the method
    for(int i = 0; i < method.size(); i++ )
    {
        // Steps are denoted by newlines in the json
        // if there is a newline detected, start the counter again and increment the step
        // as long as the loop has not reached the newline at the end of the total method string
        if(method[i] == '\n' && i < method.size() - 1)
        {
            // next recipe step
            step_enumerator++;
            // reset line width counter
            counter = 0;
            std::cout << "\n\n" << step_enumerator << ": ";
        }
        // otherwise continue printing the string and increment max line width counter
        else
        {
            std::cout << method[i];
            counter++;
        }
        // if we've gone over line length max wait for a space character to split to the line to a new line
        if(counter > line_length && method[i] == ' ')
        {
            counter = 0;
            std::cout << '\n';
        }
    }
    // place a new line after each step
    std::cout << "\n";
}

std::unordered_map<int, int> Recipe::get_recipe_ingredients() const {return recipe_ingredients;}

void Recipe::display_recipe_ingredients(std::unordered_map<int, Ingredient> ingredients_list) const
{
    std::cout << "Ingredients for " << title << ":\n";
    // iterate over the ingredients needed for the recipe, the current iteration is called ingredient, and recipe ingredients
    // are key/value pairs <uuid, amount>
    for(const auto& recipe_ingredient : recipe_ingredients)
    {
        // find the ingredient on the ingredients list of the local variable ingredient's first value, it's uuid
        auto it = ingredients_list.find(recipe_ingredient.first);

        // if current recipe ingredient amount has sentinel value then it is considered an uncountable ingredient
        if(recipe_ingredient.second != -1)
        {
            std::cout << it->second.get_name() << ": " << recipe_ingredient.second << " " << it->second.get_unit() << std::endl;
        }
        else
        {
            std::cout << it->second.get_name() << ": " << "to taste" << std::endl;
        }
    }
}
