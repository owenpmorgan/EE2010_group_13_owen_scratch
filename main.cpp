#include <iostream>
#include "Ingredient.h"
#include "MeasurementType.h"
#include "Recipe.h"
#include "IngredientList.h"
#include "WeekPlan.h"


int main() {

    IngredientList ingredientList;

    // check I am in main

//     ingredient(uuid, name, measurementtype, amount, unit)
    ingredientList.add_ingredient(Ingredient(1, "Oil", MeasurementType::VOLUME));
    ingredientList.add_ingredient(Ingredient(2, "Herbs", MeasurementType::GENERIC));
    ingredientList.add_ingredient(Ingredient(3, "Rice", MeasurementType::WEIGHT));
    ingredientList.add_ingredient(Ingredient(4, "Eggs", MeasurementType::COUNT));
    ingredientList.add_ingredient(Ingredient(5, "Black Pepper", MeasurementType::SEASONING));

    Recipe Eggs_oil("Eggs and Oil", 4);
    Eggs_oil.add_ingredient(1, 20);
    Eggs_oil.add_ingredient(4, 2);
    Eggs_oil.display_recipe_ingredients(ingredientList.get_ingredients_list());
    Eggs_oil.display_recipe_ingredients(ingredientList.get_ingredients_list());

    Recipe Pepper_bowl("Pepper In a Bowl", 8);
    Pepper_bowl.add_ingredient(5);
    Pepper_bowl.display_recipe_ingredients(ingredientList.get_ingredients_list());

    Recipe Rice_Herbs("Rice and Herbs", 4);
    Rice_Herbs.add_ingredient(3, 200);
    // add ingredient now has a constructor with just one arg that defaults the amount to GENERIC (ie no value) and
    // assings the nullopt optional int when called
    Rice_Herbs.add_ingredient(2);

//    ingredientList.get_ingredient(3).display();

    WeekPlan myWeek;

    myWeek.add_recipe(Eggs_oil, 1);
    myWeek.add_recipe(Eggs_oil, 2);
    myWeek.add_recipe(Eggs_oil, 3);
    myWeek.add_recipe(Eggs_oil, 4);
    myWeek.add_recipe(Eggs_oil, 9);
    myWeek.add_recipe(Rice_Herbs, 10);
    myWeek.add_recipe(Rice_Herbs, 13);
    myWeek.add_recipe(Rice_Herbs, 14);
    myWeek.add_recipe(Rice_Herbs, 16);
    myWeek.add_recipe(Pepper_bowl, 17);


    myWeek.display_weeks_recipes();

    myWeek.sum_total_weeks_ingredients();

    myWeek.display_total_weeks_ingredients(ingredientList.get_ingredients_list());

}
