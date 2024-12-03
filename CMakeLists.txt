cmake_minimum_required(VERSION 3.26)
project(EE2010_group_my_scratch)

# Use C++14
set(CMAKE_CXX_STANDARD 14)

# Add a target for Boost tests
add_executable(boost_tests main.cpp)

#include_directories("/opt/homebrew/include")
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories("/usr/local/boost_1_68_0")

add_executable(EE2010_group_my_scratch main.cpp
        Ingredient.cpp
        Ingredient.h
        MeasurementType.h
        Recipe.cpp
        Recipe.h
        IngredientList.cpp
        IngredientList.h
        WeekPlan.cpp
        WeekPlan.h
        Organiser.cpp
        Organiser.h
        Interface.cpp
        Interface.h
        RecipeList.cpp
        RecipeList.h)
