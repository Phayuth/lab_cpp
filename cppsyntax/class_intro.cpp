#include <cmath>
#include <iostream>

class Cylinder {
    private:
        // member variable
        double radius{1.4};
        double height{2.0};
        int *large_data_i_dont_want_to_copy = nullptr;

    public:
        // member method
        double volume() {
            return M_PI * radius * radius * height;
        }

        void show_large_data() {
            printf("Large data is integer : %i\n", *large_data_i_dont_want_to_copy);
        }

        // default contructor empty parameter
        Cylinder() = default;

        // contructor with paramters
        Cylinder(double radius_param, double height_param) {
            radius = radius_param;
            height = height_param;
        }

        // constructor with pointer
        Cylinder(double radius_param, double height_param, int large_data_i_dont_want_to_copy_param) {
            radius = radius_param;
            height = height_param;

            std::cout << "large now is nullptr: " << large_data_i_dont_want_to_copy << std::endl;

            // first we create a heap memory to store `int` data
            large_data_i_dont_want_to_copy = new int;
            // then we set that pointer to store an address of the parameter
            *large_data_i_dont_want_to_copy = large_data_i_dont_want_to_copy_param;

            std::cout << "large now is point to some address : " << large_data_i_dont_want_to_copy << std::endl;
        }

        // destructor
        ~Cylinder() {
            printf("Destructor is called.\n");

            // release the memory back to the system after class die
            delete large_data_i_dont_want_to_copy;
            large_data_i_dont_want_to_copy = nullptr;

            std::cout << "large now is deleted and setted back to nullptr: " << large_data_i_dont_want_to_copy << std::endl;
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
    // Cylinder c1;
    // printf("Volume :%f\n", c1.volume());

    Cylinder c2(2.1, 2.3, 56727985);
    c2.show_large_data();

    return 0;
}
