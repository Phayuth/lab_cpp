cmake_minimum_required(VERSION 3.0)

project(paper_torus)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/include/eigen3")
include_directories("/usr/include/ompl-1.5")

# Add subdirectories for external libraries with relative paths
add_subdirectory("../../spatial_geometry" "${CMAKE_BINARY_DIR}/spatial_geometry")
add_subdirectory("../../robot" "${CMAKE_BINARY_DIR}/robot")

# ext goal case
add_executable(paper_exts_goalset paper_exts_goalset.cpp)
target_link_libraries(paper_exts_goalset PUBLIC ompl robot spatial_geometry yaml-cpp)

# r2 space
add_executable(paper_r2s paper_r2s.cpp)
target_link_libraries(paper_r2s PUBLIC ompl robot spatial_geometry yaml-cpp)

# so2 space
add_executable(paper_so2s paper_so2s.cpp)
target_link_libraries(paper_so2s PUBLIC ompl robot spatial_geometry yaml-cpp)
