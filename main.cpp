#include <iostream>
#include "Interface.h"
#include "Ingredient.h"
#include "Recipe.h"
#include "IngredientList.h"
#include "WeekPlan.h"
#include "RecipeList.h"
#include "json.hpp"
#include <fstream>

#define BOOST_TEST_MODULE MyTestModule

// uncomment to access the test main (must comment out program main)
//#include <boost/test/included/unit_test.hpp>

// test

/*

BOOST_AUTO_TEST_CASE(F1_test_create_recipe_database)
{
    RecipeList recipe_list;
    Recipe current_recipe("A Meal", 2, "Cook It");
    recipe_list.add_recipe_to_list(current_recipe);
    BOOST_CHECK(recipe_list.get_recipe_by_id(1).get_title() == "A Meal");
    BOOST_CHECK(recipe_list.get_recipe_by_id(1).get_portions() == 2);
    BOOST_CHECK(recipe_list.get_recipe_by_id(1).get_recipe_method() == "Cook It");

}

BOOST_AUTO_TEST_CASE(F2_test_view_list_of_recipes)
{
    RecipeList recipe_list;
    Recipe current_recipe("A Meal", 2, "Cook It");
    recipe_list.add_recipe_to_list(current_recipe);

    // check that no exceptions were thrown
    BOOST_CHECK_NO_THROW(recipe_list.display_recipe_list());
}

BOOST_AUTO_TEST_CASE(F3_create_weekly_meal_plan)
{
    WeekPlan week_plan;
    // check if any exceptions were thrown
    BOOST_CHECK_NO_THROW(week_plan.display_weeks_recipes());
}

// this one rewuires a user input
BOOST_AUTO_TEST_CASE(F4_add_recipe_to_week_plan)
{
    WeekPlan week_plan;
    RecipeList recipe_list;
    Recipe current_recipe("A Meal", 2, "Cook It");
    recipe_list.add_recipe_to_list(current_recipe);
    BOOST_CHECK_NO_THROW(week_plan.add_recipe(1, &recipe_list.get_recipe_list()));
}

BOOST_AUTO_TEST_CASE(F5_remove_meal_from_meal_plan)
{
    WeekPlan week_plan;
    RecipeList recipe_list;
    Recipe current_recipe("A Meal", 2, "Cook It");
    recipe_list.add_recipe_to_list(current_recipe);
    week_plan.add_recipe(1, &recipe_list.get_recipe_list());
    week_plan.delete_meal_from_plan();
}

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

BOOST_AUTO_TEST_CASE(F3_test_get_recipe_list)
{
    RecipeList recipeList;
    BOOST_CHECK((std::is_same<decltype(recipeList.get_recipe_list()), std::map<int, Recipe>&>::value));
}
*/

// initialise json parser
using json = nlohmann::json;

 int main() {

    // unordered_map<int uuid, Ingredient ingredient>
    IngredientList ingredientList;
    // map<int recipe_id, Recipe recipe>
    RecipeList recipe_list;
    // Recipe array[max_recipes]
    WeekPlan myWeek;
    // Create the interface object to run the main app commands
    Interface interface;



/*****************************************************************************************************************
 * The Following block is all just parsing the scraped json file and adding it to the various classes
 *****************************************************************************************************************/
// open the json and parse the data to a json object called data
    std::ifstream myFile("recipes_clean.json");
    if (!myFile.is_open()) {
        std::cerr << "Failed to open JSON file." << std::endl;
        return 1;
    }
    json data = json::parse(myFile);
    myFile.close();

    // this will be incremented as new ingredients added, the uuid is a reference to an ingredient in ingredient_list
    int uuid = 0;

/*****************************************************************************************************************
 * The following outer loop (using i) collects recipe data for each in the json and makes a recipe object
 *****************************************************************************************************************/

    // loop through all recipes in the json, i is each recipe
    for(int i = 0; i < data.size(); i++)
    {
        // grab the string 'name' from the current recipe, to be used in the constructor of a new recipe
        std::string recipe_name = data[i]["name"];

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

            // get ingredient amount, some ingredient amounts are null in the json,
            // set temporary amount to sentinel value and then update with real value if not null
            int ingredient_amount = -1;

            // if the quantity field is not marked null
            if (!data[i]["ingredients"][j]["quantity"].is_null()) {
                std::string quantity_str = data[i]["ingredients"][j]["quantity"].get<std::string>();
                // and if the field can be converted to an integer
                if (!quantity_str.empty() && std::all_of(quantity_str.begin(), quantity_str.end(), ::isdigit)) {
                    // convert it to int, and store it as the ingredient quantity
                    ingredient_amount = std::stoi(quantity_str);
                }
                else
                {
                    // set all non-numericas to the sentinel value -1, which can be parsed later
                    ingredient_amount = -1;
                }
            }

            // Similarily some ingredient units are also null, set to "" and then if it is not null update with the real value
            std::string ingredient_unit = "";

            if (!data[i]["ingredients"][j]["unit"].is_null())
            {
                // get the unit from the json if it is a valid string
                ingredient_unit = data[i]["ingredients"][j]["unit"].get<std::string>();
            }

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

int user_choice;

    interface.display_intro_screen();

    // main program loop
    while (1)
    {
        user_choice = interface.display_menu();

        switch (user_choice)
        {
            case 1:
            {
                // see the weeks recipes
                interface.clear_screen();
                myWeek.display_weeks_recipes();
                break;
            }

            case 2:
            {
                // see the recipes database parsed from the recipes json file
                interface.clear_screen();
                recipe_list.display_recipe_list();
                break;
            }

            case 3:
            {
                // add a recipe to the weeks recipe list
                recipe_list.display_recipe_list();
                int min = 1;
                int max = recipe_list.get_recipe_list().size();
                int selection = interface.get_int_input(min, max);
                myWeek.add_recipe(selection, &recipe_list.get_recipe_list());
                interface.clear_screen();
                myWeek.display_weeks_recipes();
                break;
            }

            case 4:
            {
                // delete a recipe from the weeks recipe list
                interface.clear_screen();
                myWeek.display_weeks_recipes();
                myWeek.delete_meal_from_plan();
                interface.clear_screen();
                myWeek.display_weeks_recipes();
                break;
            }

            case 5:
            {
                // view the total ingredients needed, the weeks shopping list
                interface.clear_screen();
                myWeek.display_shopping_list(&ingredientList.get_ingredients_list());
                break;
            }

            case 6:
            {
                // display a method for a recipe on the list
                interface.clear_screen();
                myWeek.display_weeks_recipes();
                recipe_list.display_recipe_list();
                int min = 1;
                int max = recipe_list.get_recipe_list().size();
                int selection = interface.get_int_input(min, max);
                recipe_list.get_recipe_by_id(selection).display_recipe_method();
                break;
            }

            case 7:
            {
                // clear the week plan
                myWeek.clear_week_plan();
                interface.clear_screen();
                std::cout << "Your WeekPlan has been cleared\n\n";
                myWeek.display_weeks_recipes();
                break;
            }

            case 8:
            {
                // quit the program
                exit(0);
                break;
            }

            default:
            {
                std::cout << "Not a valid selection";
            }
        }
    }
}


