#include <iostream>
#include "Ingredient.h"
#include "MeasurementType.h"
#include "Recipe.h"
#include "IngredientList.h"

int main() {

    IngredientList ingredientList;

//     ingredient(uuid, name, measurementtype, amount, unit)
    ingredientList.add_ingredient(Ingredient(1, "Oil", MeasurementType::VOLUME, 2, "tbsp"));
    ingredientList.add_ingredient(Ingredient(2, "Herbs", MeasurementType::GENERIC));
    ingredientList.add_ingredient(Ingredient(3, "Rice", MeasurementType::WEIGHT, 200, "grams"));
    ingredientList.add_ingredient(Ingredient(4, "Eggs", MeasurementType::COUNT, 3));

    ingredientList.get_ingredient(1).display();

    ingredientList.display_total_ingredients_list();

//    oil.display();
//    herbs.display();
//    rice.display();
//    eggs.display();

}
