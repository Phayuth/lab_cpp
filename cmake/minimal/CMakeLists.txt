cmake_minimum_required(VERSION 2.6)

project(Tutorial)

add_library(math_lib math_lib.cpp)

add_executable(main main.cpp)
target_link_libraries(main math_lib)

