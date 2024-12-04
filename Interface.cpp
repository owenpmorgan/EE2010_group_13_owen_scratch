//
// Created by Owen Morgan on 18/11/2024.
//
#include<cstdlib>

#include "Interface.h"

void Interface::clear_screen()
{
    for (int i = 0; i < 20; i++) {
        std::cout << "\n";
    }
    std::cout.flush();
}

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

int Interface::display_menu()
{
    std::cout << "What would you like to do?\n";

    std::cout << "______________________\n";
    std::cout << "1 - View MealPlan\n"
                 "2 - View Recipe Database\n"
                 "3 - Add Recipe\n"
                 "4 - Delete Recipe\n"
                 "5 - View Shopping List\n"
                 "6 - Get Recipe Method\n"
                 "7 - Clear MealPlan\n"
                 "8 - Quit\n";
    std::cout << "______________________\n\n";

    int userChoice = get_int_input(1, 8);

    return userChoice;
}

int Interface::get_int_input(int min, int max) {

    // the int to be returned
    int userChoice;
    // and a counter that will give up and return 1 if too many errors
    int errorCounter = 0;

    while(true)
    {
        // if the value passed to max is greater than MAX_RECIPES it must be from the recipe list
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
                // If too many failed inputs return a 1
                std::cout << "\nToo many failed inputs! \n";
                return 1;
            }
        }
        break;
    }
    std::cout << "\n";

    return userChoice;
}
