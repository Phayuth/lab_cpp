#include <cmath>
#include <iostream>

// no using pointer
float v = 0.1;
float omega = 0;
float Ts = 0.03;

float x = 0;
float y = 0;
float t = 0;

int count = 100;

int main(int argc, char const *argv[]) {
    std::cout << "Starting Odometry" << std::endl;

    while (true) {
        x = x + v * cos(t) * Ts;
        y = y + v * sin(t) * Ts;
        t = t + omega * Ts;
        std::cout << "X = " << x << " , "
                  << "Y = " << y << " , "
                  << " T = " << t << std::endl;
    }
    return 0;
}