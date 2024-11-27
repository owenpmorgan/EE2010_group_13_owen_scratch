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


//BOOST_AUTO_TEST_CASE(test_user_ingredient)
//{
//    Ingredient ingredient(1, "Eggs", MeasurementType::COUNT);
//
//    BOOST_CHECK(ingredient.get_uuid() == 1);
//    BOOST_CHECK(ingredient.get_name() =="Eggs");
//    BOOST_CHECK(ingredient.get_measurement_type() == MeasurementType::COUNT);
//}





int main() {

    IngredientList ingredientList;
    RecipeList recipe_list;

    // Leave this here for now as it is good at picking up any errors in the json file to be parsed
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
//
//    }

// open the json and parse the data to a json object called data
    std::ifstream myFile("recipes.json");
    if (!myFile.is_open()) {
        std::cerr << "Failed to open JSON file." << std::endl;
        return 1;
    }
    json data = json::parse(myFile);
    myFile.close();

    int uuid = 0;

    // loop through all recipes in the json, i is each recipe
    for(int i = 0; i < data.size(); i++)
    {
        // grab the string 'name' from the recipe
        std::string recipe_name = data[i]["name"];

        // cout recipe name for debugging the loop
        std::cout << recipe_name << std::endl;

        int recipe_portions;
        // save string 'servings' so we can inspect it to see if it can be converted to int
        std::string servings_str = data[i]["servings"].get<std::string>();
        // check if the whole thing is numeric
        if (!servings_str.empty() && std::all_of(servings_str.begin(), servings_str.end(), ::isdigit)) {
            // if so convert it to int and that thats the quantity
            recipe_portions = std::stoi(servings_str);
        }
        else
        {
            // if not set to a default value
            recipe_portions = 1;
        }

        // set a default value for method
        std::string recipe_method = "";
        // method is an array of strings, so we need to concatenate them
        for (const auto& step : data[i]["method"])
        {
            // if there is some data
            if (!step.is_null())
            {
                // add it
                recipe_method += step.get<std::string>() + "\n"; // Combine steps with a newline
            }
        }

        // make a new recipe object with th gathered data
        Recipe current_recipe(recipe_name, recipe_portions, recipe_method);

//        std::cout << current_recipe.get_recipe_method();

        // now loop through the ingredients in the recipe
        for(int j = 0; j < data[i]["ingredients"].size(); j++)
        {
            std::string ingredient_name = data[i]["ingredients"][j]["ingredient"];
//            std::cout << "Processing ingredient: " << ingredient_name << "\n";

            // some ingredient amounts are null, set temp to -1 and then update with real value if not null
            int ingredient_amount = -1; // Default to -1 if quantity is null
            if (!data[i]["ingredients"][j]["quantity"].is_null()) {
                // similarily, some amounts are a string saying 'handfull' etc, ignore these
                // first get what we are trying to convert to int
                std::string quantity_str = data[i]["ingredients"][j]["quantity"].get<std::string>();
                // check if the whole thing is numeric
                if (!quantity_str.empty() && std::all_of(quantity_str.begin(), quantity_str.end(), ::isdigit)) {
                    // if so convert it to int and that thats the quantity
                    ingredient_amount = std::stoi(quantity_str);
                }
                else
                {
                    // if not set the sentinel value
                    ingredient_amount = -1;
                }

            }

            // some ingredient units are null, set to "" and then if it is not null update with the real value
            std::string ingredient_unit = "";
            if (!data[i]["ingredients"][j]["unit"].is_null()) {
                ingredient_unit = data[i]["ingredients"][j]["unit"].get<std::string>();

            }

            // Check if the ingredient already exists in the IngredientList by name
            int actual_uuid = -1; // Default to the current UUID if the ingredient doesn't already exist

            std::cout << "IngredientList size: " << ingredientList.get_ingredients_list().size() << "\n";

            // look for the current ingredient name in the ingredient list
            for (const auto& pair : ingredientList.get_ingredients_list())
            {
                // for each iteration, look at the name of ingredient to be added and see if it's the same as an ingredient on the list
                if (pair.second.get_name() == ingredient_name)
                {
                    // if it is, just use the existing uuid
                    actual_uuid = pair.first; // Use the existing ingredient's UUID
                    // and break the for
                    break;
                }
            }
            // if the above loop exited without the name of the ingredient being found
            if (actual_uuid == -1)
            {
                actual_uuid = uuid; // Use the current UUID
                ingredientList.add_ingredient(Ingredient(actual_uuid, ingredient_name, ingredient_unit));
                uuid++; // Increment UUID only for new ingredients
            }
            current_recipe.add_ingredient(actual_uuid, ingredient_amount);


        }

        // finally add the current_recipe to the master recipe_list
        recipe_list.add_recipe_to_list(current_recipe);
    }

    // check you can grab a recipe by id
//    std::cout << recipe_list.get_recipe_by_id(2).get_title();

ingredientList.display_total_ingredients_list();

//     ingredient(uuid, name, measurementtype)
//    ingredientList.add_ingredient(Ingredient(1, "Oil", MeasurementType::VOLUME));
//    ingredientList.add_ingredient(Ingredient(2, "Herbs", MeasurementType::GENERIC));
//    ingredientList.add_ingredient(Ingredient(3, "Rice", MeasurementType::WEIGHT));
//    ingredientList.add_ingredient(Ingredient(4, "Eggs", MeasurementType::COUNT));
//    ingredientList.add_ingredient(Ingredient(5, "Black Pepper", MeasurementType::SEASONING));

//    for (ingredient in recipe in json)

//    // recipe (title, portions)
//    Recipe Eggs_oil("Eggs and Oil", 2, "cook it");
//
////  for recipe in json
//    Eggs_oil.add_ingredient(1, 20);
//    Eggs_oil.add_ingredient(4, 2);
//    Eggs_oil.display_recipe_ingredients(ingredientList.get_ingredients_list());
//
//    Recipe Pepper_bowl("Pepper In a Bowl", 1, "make it");
//    Pepper_bowl.add_ingredient(5, -1);
//    Pepper_bowl.display_recipe_ingredients(ingredientList.get_ingredients_list());
//
//    Recipe Rice_Herbs("Rice and Herbs", 4, "cook it");
//    Rice_Herbs.add_ingredient(3, 200);
//    Rice_Herbs.add_ingredient(2, -1);

//    ingredientList.get_ingredient(3).display();


    WeekPlan myWeek;

    // bool to exit loop when program quits
    bool run = true;

//    recipe_list.display_recipe_list();


    myWeek.add_recipe(143, recipe_list.get_recipe_list());

    myWeek.display_weeks_recipes();


//    myWeek.add_recipe(2);

    myWeek.display_total_weeks_ingredients(ingredientList.get_ingredients_list());

}
