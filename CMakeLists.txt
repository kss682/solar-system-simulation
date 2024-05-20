cmake_minimum_required(VERSION 3.28)
project(solar_sys_sim)

set(CMAKE_CXX_STANDARD 23)

add_executable(solar_sys_sim src/main.cpp
        src/units/Vector.h
        src/units/Vector.cpp
        src/units/Dimension.h
        src/units/Dimension.cpp
        src/tree-elements/Element.h
        src/tree-elements/Element.cpp
        src/tree-elements/Body.h
        src/tree-elements/Body.cpp
        src/tree-elements/BoundingBox.h
        src/tree-elements/BoundingBox.cpp
        src/Tree_Creator.h
        src/Tree_Creator.cpp)