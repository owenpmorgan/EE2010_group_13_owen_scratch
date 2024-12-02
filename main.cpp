#include <iostream>
#include "Ingredient.h"
#include "MeasurementType.h"
#include "Recipe.h"
#include "IngredientList.h"
#include "WeekPlan.h"
#include "RecipeList.h"
#include <nlohmann/json.hpp>
#include <fstream>

#define BOOST_TEST_MODULE MyTestModule

// uncomment to access the test main (must comment out program main)
//#include <boost/test/included/unit_test.hpp>

using json = nlohmann::json;

/*
 * todo add clear recipes from week function to start from scratch (need a way to link recipes that are added together?)
 * todo also need to clear the shopping list in this case
 * todo create an options screen for view recipes, add recipe, clear recipe, clear all recipes etc.
 * todo add input sanitising in the organiser class that can be used in all inherited functions
 * todo maybe be able to manually add a recipe to a database
 * todo implement being able to replace recipes, or saying a recipe already exists there
 * todo
 *
 *todo servings is always 1
*/

/*

BOOST_AUTO_TEST_CASE(test_user_ingredient)
{
    Ingredient ingredient(1, "Egg", "item");

    BOOST_CHECK(ingredient.get_uuid() == 1);
    BOOST_CHECK(ingredient.get_name() =="Egg");
    BOOST_CHECK(ingredient.get_unit() == "item");
}

BOOST_AUTO_TEST_CASE(test_duplicate_ingredient_name)
{
    IngredientList ingredientList;
    // make an item and add it to the list
    Ingredient ingredient(1, "beef", "item");
    ingredientList.add_ingredient(ingredient);
    // and then try to add it again
    BOOST_CHECK_THROW(ingredientList.add_ingredient(ingredient), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_duplicate_ingredient_uuid)
{
    IngredientList ingredientList;
    // make 2 items with the same UUID
    Ingredient ingredient(1, "beef", "item");
    Ingredient ingredient2(1, "fish", "item");
    // Add the first
    ingredientList.add_ingredient(ingredient);
    // then try add the second and check exception is thrown
    BOOST_CHECK_THROW(ingredientList.add_ingredient(ingredient2), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_recipe_to_add_not_found)
{
    RecipeList recipeList;
    WeekPlan weekplan;
    BOOST_CHECK_THROW(weekplan.add_recipe(-1, &recipeList.get_recipe_list()), std::runtime_error);
}

*/

 int main() {

    // unordered_map<int uuid, Ingredient ingredient>
    IngredientList ingredientList;
    // map<int recipe_id, Recipe recipe>
    RecipeList recipe_list;
    // Recipe array[max_recipes]
    WeekPlan myWeek;

/*****************************************************************************************************************
 * Debugger for the json file
 *****************************************************************************************************************/
//    std::ifstream myFile("recipes.json");
//    if (!myFile.is_open()) {
//        std::cerr << "Failed to open JSON file." << std::endl;
//        return 1;
//    }
//    json data = json::parse(myFile);
//    myFile.close();
//
//    // test print all recipes
//    for(int i = 0; i < data.size(); i++)
//    {
//        std::cout << data[i]["name"] << std::endl;
//
//        for(int j = 0; j < data[i]["ingredients"].size(); j++)
//        {
//            std::cout << data[i]["ingredients"][j]["ingredient"] << "\t" <<
//            data[i]["ingredients"][j]["quantity"] << std::endl;
//        }
//    }
/*****************************************************************************************************************
 * End
 *****************************************************************************************************************/


/*****************************************************************************************************************
 * The Following block is all just parsing the scraped json file and adding it to the various classes
 *****************************************************************************************************************/
// open the json and parse the data to a json object called data
    std::ifstream myFile("recipes.json");
    if (!myFile.is_open()) {
        std::cerr << "Failed to open JSON file." << std::endl;
        return 1;
    }
    json data = json::parse(myFile);
    myFile.close();

    // this will be incremented as new ingredients added, the uuid is a reference to an ingredient in ingredient_list
    int uuid = 0;

/*****************************************************************************************************************
 * The following outer loop (using i) collects recipe data for each in the json and makes a recipe obejct
 *****************************************************************************************************************/

    // loop through all recipes in the json, i is each recipe
    for(int i = 0; i < data.size(); i++)
    {
        // grab the string 'name' from the current recipe, to be used in the constructor of a new recipe
        std::string recipe_name = data[i]["name"];

        // cout recipe name for debugging the loop
        // std::cout << recipe_name << std::endl;

        // grab the number of portions from the current recipe, this may not be an int, so the following checks if it is
        int recipe_portions;
        // save string 'servings' so we can inspect it to see if it can be converted to int
        std::string servings_str = data[i]["servings"].get<std::string>();
        // check if the whole thing is numeric
        if (!servings_str.empty() && std::all_of(servings_str.begin(), servings_str.end(), ::isdigit)) {
            // if so convert it to int and that that's the portion quantity
            recipe_portions = std::stoi(servings_str);
        }
        else
        {
            // if not set to a default value for recipe_portions used in constructor below
            recipe_portions = 1;
        }

        // grab the method text from the current recipe, first set a default string to be populated
        std::string recipe_method = "";
        // method is an array of strings, so we need to concatenate them
        for (const auto& step : data[i]["method"])
        {
            // if there is some data
            if (!step.is_null())
            {
                // add it to the method string, to be used in constructor below
                recipe_method += step.get<std::string>() + "\n";
            }
        }

        // make a new, temporary, recipe object with the gathered data
        Recipe current_recipe(recipe_name, recipe_portions, recipe_method);

/*****************************************************************************************************************
* The following inner loop (using j) collects recipe ingredients, populates the master ingredient list with current recipes
* ingredients and links each ingredient item to the current recipe.
*****************************************************************************************************************/

        // now loop through the ingredients in the recipe, j is an ingredient in the recipe
        for(int j = 0; j < data[i]["ingredients"].size(); j++)
        {
            // populate the ingredient name variable from the current ingredient in the recipe
            std::string ingredient_name = data[i]["ingredients"][j]["ingredient"];

            // check ingredient is cycling through correctly
            // std::cout << "Processing ingredient: " << ingredient_name << "\n";

            // get ingredient amount, some ingredient amounts are null in the json,
            // set temporary amount to sentinel value and then update with real value if not null
            int ingredient_amount = -1;

            if (!data[i]["ingredients"][j]["quantity"].is_null()) {
                // similarily, some amounts are a string saying 'handfull' etc, ignore these,
                // make sure the quantity of the current ingredient is an int.
                std::string quantity_str = data[i]["ingredients"][j]["quantity"].get<std::string>();
                // check if the whole thing is numeric
                if (!quantity_str.empty() && std::all_of(quantity_str.begin(), quantity_str.end(), ::isdigit)) {
                    // if so convert it to int and that thats the quantity
                    ingredient_amount = std::stoi(quantity_str);
                }
                else
                {
                    // if not set the sentinel value, which we can parse later when the ingredient comes up
                    ingredient_amount = -1;
                }
            }

            // Similarily some ingredient units are null, set to "" and then if it is not null update with the real value
            std::string ingredient_unit = "";

            if (!data[i]["ingredients"][j]["unit"].is_null())
            {
                // get the unit from the json if it is a valid string
                ingredient_unit = data[i]["ingredients"][j]["unit"].get<std::string>();
            }

            // check ingredient list is growing properly
            // std::cout << "IngredientList size: " << ingredientList.get_ingredients_list().size() << "\n";

            // We need to notice if a uuid is a valid, new, uuid, this sentinel value helps this
            int default_uuid = -1;

            // look for the current ingredient name in the ingredient list
            // get_ingredients_list returns unorderd_map<int, Ingrededient>
            for (const auto& pair : ingredientList.get_ingredients_list())
            {
                // check if the ingredient to be added already exists in the ingredient list (by name)
                if (pair.second.get_name() == ingredient_name)
                {
                    // if it is, just use the existing uuid, which is given by pair.first
                    default_uuid = pair.first;
                    // and break the for
                    break;
                }
            }
            // if the above loop exited without the name of the ingredient being found default_uuid will still be -1
            if (default_uuid == -1)
            {
                // so give it a new uuid
                default_uuid = uuid;
                // add the ingredient with the collated values
                ingredientList.add_ingredient(Ingredient(default_uuid, ingredient_name, ingredient_unit));
                // and increment ingredient uuid, as we have just made a new ingredient in the list, the next must have
                // the next uuid
                uuid++;
            }

            // now add the ingredient to the current recipe, using default_uuid which will have been made either a new uuid
            // or given the uuid of an existing ingredient.
            current_recipe.add_ingredient(default_uuid, ingredient_amount);
        }

        // finally add the current_recipe to the master recipe_list
        recipe_list.add_recipe_to_list(current_recipe);
    }

/*****************************************************************************************************************
 * End of json parsing block
 *****************************************************************************************************************/


    // debug tools
    // check you can grab a recipe by id
    // std::cout << recipe_list.get_recipe_by_id(2).get_title();
    //  ingredientList.display_total_ingredients_list();

/*****************************************************************************************************************
 * User interface part of program starts here
 *****************************************************************************************************************/

    recipe_list.display_recipe_list();

    myWeek.add_recipe(143, &recipe_list.get_recipe_list());
    myWeek.add_recipe(142, &recipe_list.get_recipe_list());
    myWeek.add_recipe(141, &recipe_list.get_recipe_list());

    myWeek.display_weeks_recipes();

    myWeek.display_shopping_list(&ingredientList.get_ingredients_list());

//    myWeek.clear_week_plan();
//    myWeek.display_weeks_recipes();
//    myWeek.display_total_weeks_ingredients(ingredientList.get_ingredients_list());

    myWeek.delete_meal_from_plan();
    myWeek.display_weeks_recipes();
    myWeek.display_shopping_list(&ingredientList.get_ingredients_list());

    return 0;
}


