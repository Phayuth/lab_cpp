cmake_minimum_required(VERSION 2.6)

project(Tutorial)

include_directories("include/my_math")

add_library(math_lib src/my_math/math_lib.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main math_lib)
