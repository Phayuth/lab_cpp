#define _USE_MATH_DEFINES // use this to call cmath constant value such as pi = M_PI = 3.14
#include <cmath>          // use this to use math in c++
#include <iostream>       // use this to use print etc

int count = 101;
float freq = 2 * M_PI / 30;
const int gravity = 9.81; // constant of value where we can not change it later

int func(int i, float freq) {
    unsigned long long b = pow(i, 2) + sqrt(i) * sin(freq * i) + cos(freq * i + 1); // can overflow when value become high See max min value of data type
    return b;
}

int main() {
    for (int i = 0; i < count; ++i) {
        float u = sin(freq * i); // we can define type in main as well
        float wer = func(i, freq);
        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "Step : " << i << " Sin wave is :" << u << std::endl;
        std::cout << "quater is :" << wer << std::endl;

        if (u < 0) {
            std::cout << "Negative region" << std::endl;
        } else {
            std::cout << "Positive region" << std::endl;
        }
    }
}