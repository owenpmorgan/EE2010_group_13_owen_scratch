//
// Created by Owen Morgan on 05/11/2024.
//

#include "Ingredient.h"

Ingredient::Ingredient(int uuid,
                        std::string name,
                        MeasurementType type,
                        float quantity,
                        std::string unit)
                        : uuid(uuid),
                        name(name),
                        measurement_type(type),
                        quantity(quantity),
                        unit(unit)
{
    set_default_unit();
}

// this gets called in the constructor to find the default unit
void Ingredient::set_default_unit()
{
    if (unit.empty())
    {
        switch (measurement_type)
        {
            case MeasurementType::WEIGHT:
                unit = "grams";
                break;
            case MeasurementType::VOLUME:
                unit = "ml";
                break;
            case MeasurementType::COUNT:
                unit = "item(s)";
                break;
            case MeasurementType::GENERIC:
                unit = "";
                break;
        }
    }
}

int Ingredient::get_uuid() const {return uuid;}

std::string Ingredient::get_name() const { return name;}

float Ingredient::get_quantity() const {return quantity;}

std::string Ingredient::get_unit() const {return unit;}

MeasurementType Ingredient::get_measurement_type() const {return measurement_type;}

void Ingredient::display() const {
    std::cout << name << ": ";
    if(measurement_type == MeasurementType::GENERIC){
        std::cout << "to taste";
    }
    else {
        std::cout << quantity << " " << unit;
    }
    std::cout << std::endl;
}