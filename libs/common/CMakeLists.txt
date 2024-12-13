project(CommonLibrary)

add_library(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/constants.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)