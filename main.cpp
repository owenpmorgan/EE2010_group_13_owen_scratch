#include <iostream>
#include "Ingredient.h"
#include "MeasurementType.h"
#include "Recipe.h"
#include "IngredientList.h"
#include "WeekPlan.h"
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

    std::ifstream myFile("recipes.json");
    if (!myFile.is_open()) {
        std::cerr << "Failed to open JSON file." << std::endl;
        return 1;
    }
    json data = json::parse(myFile);
    myFile.close();

    // test print all recipes
    for(int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i]["ingredients"].size(); j++)
        {
            std::cout << data[i]["ingredients"][j]["ingredient"] << "\t" <<
            data[i]["ingredients"][j]["quantity"] << std::endl;
        }

    }


//     ingredient(uuid, name, measurementtype)
    ingredientList.add_ingredient(Ingredient(1, "Oil", MeasurementType::VOLUME));
    ingredientList.add_ingredient(Ingredient(2, "Herbs", MeasurementType::GENERIC));
    ingredientList.add_ingredient(Ingredient(3, "Rice", MeasurementType::WEIGHT));
    ingredientList.add_ingredient(Ingredient(4, "Eggs", MeasurementType::COUNT));
    ingredientList.add_ingredient(Ingredient(5, "Black Pepper", MeasurementType::SEASONING));

//    for (ingredient in recipe in json)

    // recipe (title, portions)
    Recipe Eggs_oil("Eggs and Oil");

//  for recipe in json
    Eggs_oil.add_ingredient(1, 20);
    Eggs_oil.add_ingredient(4, 2);
    Eggs_oil.display_recipe_ingredients(ingredientList.get_ingredients_list());

    Recipe Pepper_bowl("Pepper In a Bowl");
    Pepper_bowl.add_ingredient(5, -1);
    Pepper_bowl.display_recipe_ingredients(ingredientList.get_ingredients_list());

    Recipe Rice_Herbs("Rice and Herbs");
    Rice_Herbs.add_ingredient(3, 200);
    Rice_Herbs.add_ingredient(2, -1);

//    ingredientList.get_ingredient(3).display();

    WeekPlan myWeek;

    // bool to exit loop when program quits
    bool run = true;


    myWeek.add_recipe(Eggs_oil);

    myWeek.add_recipe(Rice_Herbs);

//  myWeek.add_recipe(Rice_Herbs);

//  myWeek.add_recipe(Pepper_bowl);

    myWeek.display_weeks_recipes();

    myWeek.display_total_weeks_ingredients(ingredientList.get_ingredients_list());

}
