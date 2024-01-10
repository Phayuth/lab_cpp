#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

class GenericClass {
    private:
        /* data */
    public:
        GenericClass(/* args */); // constructor prototype
        ~GenericClass();          // deconstructor prototype

        void setter();
        double getter();
};

GenericClass::GenericClass(/* args */) // constructor definition implement
{
}

GenericClass::~GenericClass() = default; // default deconstructor

void GenericClass::setter() {
}

double GenericClass::getter() {
}