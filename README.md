![](/cover.png)

## Compile CPP Command
```
g++ -o runProgram simple_calculator.cpp
```

## Sublime Text 3 Build System
New Build System -> Paste Below Command -> Save
```
{"cmd": ["g++", "-o" , "${file_path}/${file_base_name}" ,"*.cpp"]}
```
## Data type / byte / range
![](https://www.zseries.in/computer%20science%20lab/cp/images/datatype%20table.png)

In coding
```
#include <limits>
int imin = std::numeric_limits<int>::min(); // minimum value
int imax = std::numeric_limits<int>::max();
float fmin = std::numeric_limits<float>::min(); // minimum positive value
float fmax = std::numeric_limits<float>::max();
```