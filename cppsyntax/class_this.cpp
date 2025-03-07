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

        void show_info() {
            printf("Radius : %f\n", radius);
            printf("Large data is integer : %i\n", *large_data_i_dont_want_to_copy);
        }

        // default contructor empty parameter
        Cylinder() = default;

        // constructor with pointer
        Cylinder(double radius_param, double height_param, int large_data_i_dont_want_to_copy_param) {
            this->radius = radius;
            this->height = height;

            large_data_i_dont_want_to_copy = new int;
            *large_data_i_dont_want_to_copy = large_data_i_dont_want_to_copy_param;

            std::cout << "The object is created at : " << this << std::endl;
        }

        // destructor
        ~Cylinder() {
            // release the memory back to the system after class die
            delete large_data_i_dont_want_to_copy;
            large_data_i_dont_want_to_copy = nullptr;
        }

        // setter with value
        void setRadius(double radius) {
            this->radius = radius;
        }

        // setter with pointer
        void setLargeData(int data) {
            *(this->large_data_i_dont_want_to_copy) = data;
        }

        // return pointer to the current object
        Cylinder *setRadiusReturnPtr(double radius) {
            this->radius = radius;
            return this;
        }
        Cylinder *setLargeDataReturnPtr(int data) {
            *(this->large_data_i_dont_want_to_copy) = data;
            return this;
        }

        // return reference
        Cylinder &setRadiusReturnRef(double radius) {
            this->radius = radius;
            return *this;
        }
        Cylinder &setLargeDataReturnRef(int data) {
            *(this->large_data_i_dont_want_to_copy) = data;
            return *this;
        }
};

class T {
        int x;

        void foo() {
            x = 6;       // same as this->x = 6;
            this->x = 5; // explicit use of this->
        }

        void foo() const {
            //  x = 7; // Error: *this is constant
        }

        void foo(int x) // parameter x shadows the member with the same name
        {
            this->x = x; // unqualified x refers to the parameter
                         // 'this->' required for disambiguation
        }

        int y;
        T(int x) : x(x),      // uses parameter x to initialize member x
                   y(this->x) // uses member x to initialize member y
        {}

        T &operator=(const T &b) {
            x = b.x;
            return *this; // many overloaded operators return *this
        }
};

int main(int argc, char const *argv[]) {
    Cylinder c2(2.1, 2.3, 56727985);
    c2.show_info();
    c2.setRadius(212.2);
    c2.setLargeData(213213);
    c2.show_info();

    // chain called with pointer
    c2.setRadiusReturnPtr(44.3)->setLargeDataReturnPtr(44112);
    c2.show_info();

    // chain called with reference
    c2.setRadiusReturnRef(76.4).setLargeDataReturnRef(53421);
    c2.show_info();
    return 0;
}
