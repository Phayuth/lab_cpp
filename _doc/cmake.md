# Cmake Quickstart
cmake need CMakeLists.txt for giving instruction on building the code. The minimum CMakeLists.txt is:
```
cmake_minimum_required (VERSION 2.6)
project (name_of_proj)
add_executable(name_of_ext source_file.cpp)
```
- Create a folder name ```'build'```
- Inside folder ```'build'``` call ``` cmake .. ```
- Then call ```cmake --build . --config Release```
- If we want to compile the code again after modification, simiply call ```make```

# Cmake Tutorial
cmake c++ pratice [following](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)