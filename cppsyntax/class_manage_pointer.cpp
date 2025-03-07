#include <cmath>
#include <iostream>
// manage pointer in class with new and delete
// new and delete are used to allocate and deallocate memory in the heap.

class Cylinder {
    private:
        // member variable
        double radius{1.4};
        double height{2.0};

    public:
        // member method
        double volume() {
            return M_PI * radius * radius * height;
        }

        // default contructor empty parameter
        Cylinder() = default;

        // contructor with paramters
        Cylinder(double radius_param, double height_param) {
            radius = radius_param;
            height = height_param;
        }

        // setter getter
        void setRadius(double radius_param) {
            radius = radius_param;
        }

        double getRadius() {
            return radius;
        }
};

int main(int argc, char const *argv[]) {
    // stack object
    Cylinder c1(1.2, 2.1);
    printf("Volume :%f\n", c1.volume());

    // heap object
    Cylinder *c2 = new Cylinder(2.5, 11.5);
    printf("Volume :%f\n", (*c2).volume());
    printf("Volume :%f\n", c2->volume());
    delete c2;
    c2 = nullptr;

    return 0;
}
