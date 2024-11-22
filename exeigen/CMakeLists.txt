cmake_minimum_required(VERSION 3.0)

project(exeigen)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/include/eigen3")

add_executable(compute compute.cpp)
add_executable(create_array create_array.cpp)
add_executable(create_matrix create_matrix.cpp)
add_executable(create_vector create_vector.cpp)
add_executable(knn knn.cpp)
