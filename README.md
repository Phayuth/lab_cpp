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
## Data Type and Range
|Type|Bits|Range|
|:---:|:---:|:---:|
|Byte|8|-128 to +127|
|char|8|-128 to +127|
|unsigned char|8|0 to 255|
|signed char|8|-128 to +127|
|int|16|-32768 to +32767|
|unsigned int|16|0 to +65535|
|signed int|16|-32768 to +32767|
|short int|16|-32768 to +32767|
|unsigned short int|16|0 to +65535|
|signed short int|16|-32768 to +32767|
|long int|32|-2147483648 to +2147483648|
|unsigned long int|32|0 to +4294967295|
|signed long int|32|-2147483648 to +2147483648|
|float|32|3.4E-38 to 3.4E+38|
|double|64|1.7E-308 to 1.7E+308|
|long double|80|3.4E-4932 to 3.4E+4932|
```
#include <limits>
int imin = std::numeric_limits<int>::min(); // minimum value
int imax = std::numeric_limits<int>::max();
float fmin = std::numeric_limits<float>::min(); // minimum positive value
float fmax = std::numeric_limits<float>::max();
```
