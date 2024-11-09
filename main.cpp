#include <iostream>
#include "Ingredient.h"
#include "MeasurementType.h"
#include "Recipe.h"
#include "IngredientList.h"
#include "WeekPlan.h"


int main() {

    IngredientList ingredientList;

//     ingredient(uuid, name, measurementtype, amount, unit)
    ingredientList.add_ingredient(Ingredient(1, "Oil", MeasurementType::VOLUME));
    ingredientList.add_ingredient(Ingredient(2, "Herbs", MeasurementType::GENERIC));
    ingredientList.add_ingredient(Ingredient(3, "Rice", MeasurementType::WEIGHT));
    ingredientList.add_ingredient(Ingredient(4, "Eggs", MeasurementType::COUNT));
    ingredientList.add_ingredient(Ingredient(5, "Black Pepper", MeasurementType::SEASONING));

    Recipe Eggs_oil("Eggs and Oil");

    Eggs_oil.add_ingredient(1, 20);
    Eggs_oil.add_ingredient(4, 2);

    Eggs_oil.display_recipe_ingredients();

    Recipe Rice_Herbs("Rice and Herbs");
    Rice_Herbs.add_ingredient(3, 200);
    Rice_Herbs.add_ingredient(2);


    ingredientList.get_ingredient(3).display();

    WeekPlan myWeek;

    myWeek.add_recipe(Eggs_oil, 1);
    myWeek.add_recipe(Eggs_oil, 2);
    myWeek.add_recipe(Eggs_oil, 3);
    myWeek.add_recipe(Eggs_oil, 4);
    myWeek.add_recipe(Eggs_oil, 9);

    myWeek.display_weeks_recipes();

    myWeek.sum_total_ingredients();

    myWeek.display_total_ingredients();

}
