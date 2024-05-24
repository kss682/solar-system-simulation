cmake_minimum_required(VERSION 3.28)
project(solar_system_stimulation)

set(CMAKE_CXX_STANDARD 23)

# Include FetchContent module
include(FetchContent)

# Fetch spdlog
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1  # Use the desired version or branch
)

FetchContent_MakeAvailable(spdlog)

# GTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(solar_system_stimulation src/main.cpp
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

# Link spdlog to your executable
target_link_libraries(solar_system_stimulation PRIVATE spdlog::spdlog)

# Optionally, you can set compile definitions and options for spdlog
target_compile_definitions(solar_system_stimulation PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO)

enable_testing()

add_executable(
        solar_system_stimulation_test
        src/units/dimension.cpp
        src/units/dimension.h
        src/units/position_vector.cpp
        src/units/position_vector.h
        test/test.cc
        test/units/dimension/dimension_tests.cc
        test/units/dimension/position_vector.cc
)
target_link_libraries(
        solar_system_stimulation_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(solar_system_stimulation_test)