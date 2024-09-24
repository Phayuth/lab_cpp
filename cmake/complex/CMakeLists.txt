cmake_minimum_required (VERSION 2.6)

project (Tutorial)

include_directories("include/my_math")

add_library(MathFunctions src/my_math/math_lib.cpp)
add_executable(Tutorial src/tutorial.cpp)

target_link_libraries(Tutorial MathFunctions)