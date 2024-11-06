//
// Created by Owen Morgan on 05/11/2024.
//

#include "Recipe.h"

Recipe::Recipe(std::string title)
              : title(title)
{

}

void Recipe::add_ingredient(const Ingredient &ingredient)
{
    ingredients.push_back(ingredient);
}

void Recipe::display_recipe_ingredients() const
{
    std::cout << "Ingredients for " << title << ":\n";
    for(const auto& ingredient : ingredients)
    {
        ingredient.display();
    }
}