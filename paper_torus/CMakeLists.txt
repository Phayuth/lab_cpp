cmake_minimum_required(VERSION 3.0)

project(paper_torus)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/include/eigen3")

# g++ -std=c++11 -I /usr/include/eigen3 paper_r2s.cpp -o use_rrt_r2 -lompl

# # find alt
# add_executable(findalt findaltconfig.cpp)
# target_link_libraries(findalt PUBLIC ompl)

# real vector2 space
add_executable(paper_r2s paper_r2s.cpp)
target_link_libraries(paper_r2s PUBLIC ompl)

# so2 space
add_executable(paper_so2s paper_so2s.cpp)
target_link_libraries(paper_so2s PUBLIC ompl)

# real vector2 space with goalset
add_executable(paper_exts_goalset paper_exts_goalset.cpp)
target_link_libraries(paper_exts_goalset PUBLIC ompl)