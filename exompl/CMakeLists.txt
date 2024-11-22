cmake_minimum_required(VERSION 3.0)

project(exompl)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/include/eigen3")

# g++ -std=c++11 -I /usr/include/eigen3 paper_r2s.cpp -o use_rrt_r2 -lompl

# real vector2 space
add_executable(use_rrt_r2 paper_r2s.cpp)
target_link_libraries(use_rrt_r2 PUBLIC ompl)

# so2 space
add_executable(use_rrt_so2 paper_so2s.cpp)
target_link_libraries(use_rrt_so2 PUBLIC ompl)

# real vector2 space with goalset
add_executable(use_rrt_goalset paper_exts_goalset.cpp)
target_link_libraries(use_rrt_goalset PUBLIC ompl)

# find alt
# add_executable(findalt findaltconfig.cpp)
# target_link_libraries(findalt PUBLIC ompl)

# test
add_executable(test_calculate test_calculate.cpp)
target_link_libraries(test_calculate PUBLIC ompl)

add_executable(test_r2s_rrt test_r2s_rrt.cpp)
target_link_libraries(test_r2s_rrt PUBLIC ompl)

add_executable(test_r6s_rrtstar test_r6s_rrtstar.cpp)
target_link_libraries(test_r6s_rrtstar PUBLIC ompl)

add_executable(test_so2 test_so2.cpp)
target_link_libraries(test_so2 PUBLIC ompl)

