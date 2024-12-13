cmake_minimum_required(VERSION 3.10)
project(simulator)

set(ALL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MemoryDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RegisterDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Processor.cpp
    )

# Create executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Include libraries
target_link_libraries(${PROJECT_NAME}
    CommonLibrary
)

# Set the destination directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/simulator)