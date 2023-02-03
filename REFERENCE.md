### Simple Compile
```
g++ -o runProgram simple_calculator.cpp
```

### Cmake Quickstart
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

### Cmake Tutorial
cmake c++ pratice [following](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

### Sublime Text 3 Build System
New Build System -> Paste Below Command -> Save
```
{"cmd": ["g++", "-o" , "${file_path}/${file_base_name}" ,"*.cpp"]}
```

### Data Type and Range
|        Type        | Bits |            Range           |
|:------------------:|:----:|:--------------------------:|
|        Byte        |   8  |        -128 to +127        |
|        char        |   8  |        -128 to +127        |
|    unsigned char   |   8  |          0 to 255          |
|     signed char    |   8  |        -128 to +127        |
|         int        |  16  |      -32768 to +32767      |
|    unsigned int    |  16  |         0 to +65535        |
|     signed int     |  16  |      -32768 to +32767      |
|      short int     |  16  |      -32768 to +32767      |
| unsigned short int |  16  |         0 to +65535        |
|  signed short int  |  16  |      -32768 to +32767      |
|      long int      |  32  | -2147483648 to +2147483648 |
|  unsigned long int |  32  |      0 to +4294967295      |
|   signed long int  |  32  | -2147483648 to +2147483648 |
|        float       |  32  |     3.4E-38 to 3.4E+38     |
|       double       |  64  |    1.7E-308 to 1.7E+308    |
|     long double    |  80  |   3.4E-4932 to 3.4E+4932   |

### ROS Data Type compare with C++ and Python
| Primitive Type |          Serialization          |      C++      |     Python2    |     Python3    |
|:--------------:|:-------------------------------:|:-------------:|:--------------:|:--------------:|
|       bool     |        unsigned 8-bit int       |    uint8_t    |      bool      |      bool      |
|       int8     |         signed 8-bit int        |     int8_t    |       int      |       int      |
|      uint8     |        unsigned 8-bit int       |    uint8_t    |       int      |       int      |
|      int16     |        signed 16-bit int        |    int16_t    |       int      |       int      |
|      uint16    |       unsigned 16-bit int       |    uint16_t   |       int      |       int      |
|      int32     |        signed 32-bit int        |    int32_t    |       int      |       int      |
|      uint32    |       unsigned 32-bit int       |    uint32_t   |       int      |       int      |
|      int64     |        signed 64-bit int        |    int64_t    |      long      |       int      |
|      uint64    |       unsigned 64-bit int       |    uint64_t   |      long      |       int      |
|     float32    |        32-bit IEEE float        |     float     |      float     |      float     |
|     float64    |        64-bit IEEE float        |     double    |      float     |      float     |
|      string    |           ascii string          |  std::string  |       str      |      bytes     |
|       time     | secs/nsecs unsigned 32-bit ints |   ros::Time   |   rospy.Time   |   rospy.Time   |
|     duration   |  secs/nsecs signed 32-bit ints  | ros::Duration | rospy.Duration | rospy.Duration |
