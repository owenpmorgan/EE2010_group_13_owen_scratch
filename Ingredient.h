//
// Created by Owen Morgan on 05/11/2024.
//

#include<iostream>
#include "MeasurementType.h"

#ifndef EE2010_GROUP_MY_SCRATCH_INGREDIENT_H
#define EE2010_GROUP_MY_SCRATCH_INGREDIENT_H


class Ingredient
{
private:
    int uuid;
    std::string name;
    MeasurementType measurement_type;
    float quantity;
    std::string unit;
public:
    Ingredient(int uuid,
               std::string name,
               MeasurementType type,
               float quantity = 0,
               std::string unit = "");

    int get_uuid() const;
    void set_default_unit();
    std::string get_name() const;
    float get_quantity() const;
    std::string get_unit() const;
    MeasurementType get_measurement_type() const;
    void display() const;
};


#endif //EE2010_GROUP_MY_SCRATCH_INGREDIENT_H
