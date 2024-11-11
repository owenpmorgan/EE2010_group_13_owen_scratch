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
    std::string unit;

public:
    //constructor
    Ingredient(int uuid,
               std::string name,
               MeasurementType type,
               std::string unit = "");

    // getters
    int get_uuid() const;
    std::string get_name() const;
    std::string get_unit() const;
    MeasurementType get_measurement_type() const;

    // auto setter (from measurement type)
    void set_default_unit();

    // other methods
    void display() const;
};


#endif //EE2010_GROUP_MY_SCRATCH_INGREDIENT_H
