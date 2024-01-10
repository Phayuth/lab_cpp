# Simple Compile
```
g++ -o runProgram simple_calculator.cpp
```

# Sublime Text 3 Build System
New Build System -> Paste Below Command -> Save
```
{"cmd": ["g++", "-o" , "${file_path}/${file_base_name}" ,"*.cpp"]}
```