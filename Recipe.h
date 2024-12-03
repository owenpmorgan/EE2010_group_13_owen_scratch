//
// Created by Owen Morgan on 05/11/2024.
//

#include "Ingredient.h"
#include "IngredientList.h"
#include "IngredientList.h"
#include "MeasurementType.h"

#ifndef EE2010_GROUP_MY_SCRATCH_RECIPE_H
#define EE2010_GROUP_MY_SCRATCH_RECIPE_H

class Recipe
{

private:
    std::string title;
    int portions;
    // first is ingredient's uuid, second int amount
    std::unordered_map<int, int> recipe_ingredients;
    std::string method;



public:
    Recipe(std::string title, int portions, std::string method); // constructor
    Recipe() : title("Unnamed Recipe") {}  // Default constructor if no args passed
    ~Recipe() = default;

    void add_ingredient(const int uuid, int amount);

    std::string get_title() const;
    std::unordered_map<int, int> get_recipe_ingredients() const;
//    int get_amount(int);
    int get_portions() const;
    std::string get_recipe_method() const;

    void display_recipe_ingredients(std::unordered_map<int, Ingredient>) const;

};


#endif //EE2010_GROUP_MY_SCRATCH_RECIPE_H
