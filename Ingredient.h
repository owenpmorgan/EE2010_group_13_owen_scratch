//
// Created by Owen Morgan on 05/11/2024.
//

#include<iostream>

#ifndef EE2010_GROUP_MY_SCRATCH_INGREDIENT_H
#define EE2010_GROUP_MY_SCRATCH_INGREDIENT_H


class Ingredient
{
private:
    int uuid;
    std::string name;
    std::string unit;

public:
    //constructor
    Ingredient(int uuid,
               std::string name,
               std::string unit = "");

    // destructor
    ~Ingredient() = default;


    // getters
    int get_uuid() const;
    std::string get_name() const;
    std::string get_unit() const;

    // other methods
    void display() const;
};


#endif //EE2010_GROUP_MY_SCRATCH_INGREDIENT_H
