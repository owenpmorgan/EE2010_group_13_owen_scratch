//
// Created by Owen Morgan on 11/11/2024.
//

#include <iostream>
#include <stdexcept>
#include <sstream>

#ifndef EE2010_GROUP_MY_SCRATCH_ORGANISER_H
#define EE2010_GROUP_MY_SCRATCH_ORGANISER_H

class Organiser
{
protected:
    static const int MAX_RECIPES = 21;  // Fixed size of 21

public:

        virtual int get_int_input(int min = 0, int max = 100) = 0;
        virtual ~Organiser() = default;

};




#endif //EE2010_GROUP_MY_SCRATCH_ORGANISER_H
