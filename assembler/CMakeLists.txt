cmake_minimum_required(VERSION 3.10)
project(assembler)

set(ALL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LexicalAnalyzer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SyntaxAnalyzer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Generator.cpp
    )

# Create executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set the destination directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/assembler)