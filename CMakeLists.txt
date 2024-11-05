cmake_minimum_required(VERSION 3.26)
project(EE2010_group_my_scratch)

set(CMAKE_CXX_STANDARD 17)

add_executable(EE2010_group_my_scratch main.cpp
        Ingredient.cpp
        Ingredient.h
        MeasurementType.h
        Recipe.cpp
        Recipe.h
        IngredientList.cpp
        IngredientList.h)
