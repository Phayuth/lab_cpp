# Simple compile
```bash
g++ -o runProgram simple_calculator.cpp
```

# OMPL compile
```bash
g++ -std=c++11 -o rrt_planner use_rrt.cpp -lompl -I /usr/include/eigen3
```

# CUDA compile
```bash
nvcc hello.cu -o hello
```

# Sublime Text 3 Build System
New Build System -> Paste Below Command -> Save
```json
{"cmd": ["g++", "-o" , "${file_path}/${file_base_name}" ,"*.cpp"]}
```