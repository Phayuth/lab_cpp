cmake_minimum_required (VERSION 2.6)

project (Tutorial) 

add_library(MathFunctions math_lib.cpp) 
add_executable(Tutorial tutorial.cpp)

target_link_libraries(Tutorial MathFunctions)

