cmake_minimum_required(VERSION 3.28)
project(solar_sys_sim)

set(CMAKE_CXX_STANDARD 23)

add_executable(solar_sys_sim src/main.cpp
        src/barnes_hut.cpp
        src/barnes_hut.hpp
        src/node.cpp
        src/node.cpp)