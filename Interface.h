//
// Created by Owen Morgan on 18/11/2024.
//

#include "Organiser.h"

#ifndef EE2010_GROUP_MY_SCRATCH_INTERFACE_H
#define EE2010_GROUP_MY_SCRATCH_INTERFACE_H


class Interface : public Organiser
{

public:

    void clear_screen();
    virtual int get_int_input(int, int) override;
    void display_intro_screen();
    int display_menu();

private:

};


#endif //EE2010_GROUP_MY_SCRATCH_INTERFACE_H
