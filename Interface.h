//
// Created by Owen Morgan on 18/11/2024.
//

#include "Organiser.h"

#ifndef EE2010_GROUP_MY_SCRATCH_INTERFACE_H
#define EE2010_GROUP_MY_SCRATCH_INTERFACE_H

// inherit from organiser (pure virtual) for get_int_input()
class Interface : public Organiser
{

public:
    static void clear_screen();
    // redefine this inherited function
    int get_int_input(int, int) override;

    static void display_intro_screen();
    int display_menu();

private:

};


#endif //EE2010_GROUP_MY_SCRATCH_INTERFACE_H
