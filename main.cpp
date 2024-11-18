#include <iostream>
#include "Ingredient.h"
#include "MeasurementType.h"
#include "Recipe.h"
#include "IngredientList.h"
#include "WeekPlan.h"

/*
 * todo add clear recipes from week function to start from scratch (need a way to link recipes that are added together?)
 * todo also need to clear the shopping list in this case
 * todo create an options screen for view recipes, add recipe, clear recipe, clear all recipes etc.
 * todo add input sanitising in the organiser class that can be used in all inherited functions
 * todo maybe do the same for clear individual recipes considering portions, eg, you want to delete a 4 portion meal, when you delet the
 * first it asks you to 'clear 4 more of the same recipe'
 * todo maybe be able to manually add a recipe to a database
 * todo implement being able to replace recipes, or saying a recipe already exists there
 * todo
*/
int main() {

    IngredientList ingredientList;

//     ingredient(uuid, name, measurementtype)
    ingredientList.add_ingredient(Ingredient(1, "Oil", MeasurementType::VOLUME));
    ingredientList.add_ingredient(Ingredient(2, "Herbs", MeasurementType::GENERIC));
    ingredientList.add_ingredient(Ingredient(3, "Rice", MeasurementType::WEIGHT));
    ingredientList.add_ingredient(Ingredient(4, "Eggs", MeasurementType::COUNT));
    ingredientList.add_ingredient(Ingredient(5, "Black Pepper", MeasurementType::SEASONING));

    // recipe (title, portions)
    Recipe Eggs_oil("Eggs and Oil", 1);
    Eggs_oil.add_ingredient(1, 20);
    Eggs_oil.add_ingredient(4, 2);
    Eggs_oil.display_recipe_ingredients(ingredientList.get_ingredients_list());

    Recipe Pepper_bowl("Pepper In a Bowl", 8);
    Pepper_bowl.add_ingredient(5);
    Pepper_bowl.display_recipe_ingredients(ingredientList.get_ingredients_list());

    Recipe Rice_Herbs("Rice and Herbs", 4);
    Rice_Herbs.add_ingredient(3, 200);
    Rice_Herbs.add_ingredient(2);

//    ingredientList.get_ingredient(3).display();

    WeekPlan myWeek;

    // bool to exit loop when program quits
    bool run = true;

//    while(run){
//
//        std::cout << "Pick an option: " << std::endl;
//
//    }

    myWeek.add_recipe(Eggs_oil);

    myWeek.add_recipe(Rice_Herbs);

//  myWeek.add_recipe(Rice_Herbs);

//  myWeek.add_recipe(Pepper_bowl);

    myWeek.display_weeks_recipes();

    myWeek.display_total_weeks_ingredients(ingredientList.get_ingredients_list());

}
