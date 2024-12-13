cmake_minimum_required(VERSION 3.5)
project(ArchitectureOfComputer)

# CMake standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options to build different components
option(BUILD_ASM "Build the assemler application." ON)
option(BUILD_SIM "Build the simulator application." ON)

add_subdirectory(libs/common)

if(BUILD_ASM)
    add_subdirectory(assembler)
endif()

if(BUILD_SIM)
    add_subdirectory(simulator)
endif()