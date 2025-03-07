cmake_minimum_required(VERSION 3.0)

project(paper_agriplanner)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/include/eigen3"
                    "/home/yuth/ws_yuthdev/lab_cpp/paper_agriplanner")

set(source_files
    mypn_usage.cpp
    mypn_rrtstarconnect.h
    mypn_rrtstarconnect.cpp)

add_executable(mypn_usage ${source_files})
target_link_libraries(mypn_usage PUBLIC ompl)