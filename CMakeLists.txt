cmake_minimum_required(VERSION 3.28)
project(solar_sys_sim)

set(CMAKE_CXX_STANDARD 23)

add_executable(solar_sys_sim src/main.cpp
        src/units/dimension.cpp
        src/units/dimension.h
        src/units/position_vector.cpp
        src/units/position_vector.h
        src/tree-elements/box.cpp
        src/tree-elements/box.h
        src/tree-elements/body.cpp
        src/tree-elements/body.h
        src/barnes_hut.cpp
        src/barnes_hut.hpp)