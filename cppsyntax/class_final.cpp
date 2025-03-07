#include <iostream>
// final keyword is used to prevent the method to be overridden as it is the final implementation of the method.

class Shape {
    public:
        std::string desc;

        static int count;

        Shape(const std::string &desc) : desc(desc) {
            count++;
        }

        ~Shape() {
            count--;
        }

        // final keyword is used to prevent the method to be overridden
        virtual void get_count() const final {
            std::cout << count << std::endl;
        }
};

class Ellipse final : public Shape {
    public:
        double xr;
        double yr;
        static int count;

        Ellipse(const std::string &desc, double xr, double yr) : Shape(desc), xr(xr), yr(yr) {
            count++;
        }

        ~Ellipse() {
            count--;
        }

        // compiler error !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // void get_count() const override {
        //     std::cout << count << std::endl;
        // }
};

// compiler error !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// class Ellipsoid : public Ellipse {
//     public:
//         double zr;
//         static int count;

//         Ellipsoid(const std::string &desc, double xr, double yr, double zr) : Ellipse(desc, xr, yr), zr(zr) {
//             count++;
//         }
// };

int Shape::count = 0;
int Ellipse::count = 0;

int main(int argc, char const *argv[]) {
    Shape s1("ID 1");
    std::cout << Shape::count << std::endl;

    Ellipse e1("ID 1", 1.0, 2.0);
    std::cout << Shape::count << std::endl;
    std::cout << Ellipse::count << std::endl;
    return 0;
}
