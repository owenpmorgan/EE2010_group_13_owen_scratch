//
// Created by Owen Morgan on 05/11/2024.
//

#include "Ingredient.h"

// constructor
Ingredient::Ingredient(int uuid,
                        std::string name,
                        std::string unit)
                        : uuid(uuid),
                        name(name),
                        unit(unit){}

int Ingredient::get_uuid() const {return uuid;}

std::string Ingredient::get_name() const {return name;}

std::string Ingredient::get_unit() const {return unit;}

void Ingredient::display() const
{
    std::cout << name << ", " << unit << std::endl;
}