//
// Created by Owen Morgan on 18/11/2024.
//
#include<cstdlib>

#include "Interface.h"
#include <iostream>

// ANSI escape codes do not work in clion output console, so use a scroll to simulate clear screen
void Interface::clear_screen()
{
#if defined(__APPLE__)
    system("clear");
#else
    std::cout << "\033[2J\033[H";
#endif
}

// One time title screen to be displayed at app start
void Interface::display_intro_screen() {
    std::cout <<
    "___  ___           _______ _\n"
    "|  \\/  |          | | ___ \\ |\n"
    "| .  . | ___  __ _| | |_/ / | __ _ _ __\n"
    "| |\\/| |/ _ \\/ _` | |  __/| |/ _` | '_ \\ \n"
    "| |  | |  __/ (_| | | |   | | (_| | | | |\n"
    "\\_|  |_/\\___|\\__,_|_\\_|   |_|\\__,_|_| |_|\n\n\n";

    std::cout <<
    "Welcome to Group 13's meal planner app. You pick the recipes, we sum\n"
    "up the ingredients and give you a handy weekly shopping list!\n\n"
    "Your recipes database has been succesfully built.\n\n";
}

// rolling main menu for app interaction
int Interface::display_menu()
{
    std::cout << "What would you like to do?\n";

    std::cout << "______________________\n";
    std::cout << "1 - View MealPlan\n"
                 "2 - View Recipe Database\n"
                 "3 - Add Recipe to MealPlan\n"
                 "4 - Delete Recipe from MealPlan\n"
                 "5 - View the Weeks Shopping List\n"
                 "6 - View a Recipe Method\n"
                 "7 - Clear MealPlan\n"
                 "8 - Quit\n";
    std::cout << "______________________\n\n";

    // get_int_input takes max and min possible values to prevent out of bounds
    int userChoice = get_int_input(1, 8);

    return userChoice;
}

// polymorphic re-definiton of get_int_input for use in interface
int Interface::get_int_input(int min, int max) {

    // the input sanitised int to be returned
    int userChoice;
    // and a counter that will give up and return 1 if too many errors
    int errorCounter = 0;

    while(true)
    {
        // If called with a large max it will be from the recipe list, so display a more relevant message in this case
        if(max > MAX_RECIPES)
        {
            std::cout << "Please select a meal: ";
        }
        else
        {
            std::cout << "Enter the number of your choice: ";
        }
        // While not a valid entry clear cin and try again
        while(!(std::cin >> userChoice) || userChoice < min || userChoice > max)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please input a number, between " << min << " and " << max << ": ";
            errorCounter++;
            if(errorCounter > 3)
            {
                // If too many failed inputs return a 1, (to avoid getting stuck)
                std::cout << "\nToo many failed inputs! \n";
                return 1;
            }
        }
        break;
    }
    std::cout << "\n";

    return userChoice;
}
