//
// Created by Owen Morgan on 05/11/2024.
//

#include "Ingredient.h"

Ingredient::Ingredient(int uuid,
                        std::string name,
                        MeasurementType type,
                        std::string unit)
                        : uuid(uuid),
                        name(name),
                        measurement_type(type),
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
            case MeasurementType::SEASONING:
                unit = "to taste";
                break;
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

std::string Ingredient::get_name() const {return name;}

std::string Ingredient::get_unit() const {return unit;}

MeasurementType Ingredient::get_measurement_type() const {return measurement_type;}

void Ingredient::display() const {

    std::cout << name << ", " << unit << std::endl;
}