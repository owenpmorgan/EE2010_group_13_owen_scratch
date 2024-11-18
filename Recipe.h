//
// Created by Owen Morgan on 05/11/2024.
//

#include "Ingredient.h"
#include "IngredientList.h"
#include "IngredientList.h"
#include "MeasurementType.h"

#ifndef EE2010_GROUP_MY_SCRATCH_RECIPE_H
#define EE2010_GROUP_MY_SCRATCH_RECIPE_H

class Recipe : public IngredientList
{

private:
    std::string title;
    std::unordered_map<int, std::optional<int>> recipe_ingredients;
    int portions;

public:
    Recipe(std::string title, int portions);
    Recipe() : title("Unnamed Recipe", 0) {}  // Default constructor

    void add_ingredient(const int uuid, int amount);
    void add_ingredient(const int uuid);

    std::string get_title() const;
    std::unordered_map<int, std::optional<int>> get_recipe_ingredients() const;
    std::optional<int> get_amount(int);
    int get_portions() const;

    void display_recipe_ingredients(std::unordered_map<int, Ingredient>) const;

};


#endif //EE2010_GROUP_MY_SCRATCH_RECIPE_H
