#include <iostream>
// static variable is shared among all instances of the class.

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

        virtual void get_count() const {
            std::cout << count << std::endl;
        }
};

class Ellipse : public Shape {
    public:
        double xr;
        double yr;
        static int count;

        Ellipse(const std::string &desc, double xr, double yr)
            : Shape(desc), xr(xr), yr(yr) {
            count++;
        }

        ~Ellipse() {
            count--;
        }

        void get_count() const override {
            std::cout << count << std::endl;
        }
};

// static variable must be initialized outside the class
// put in header file
int Shape::count = 0;
int Ellipse::count = 0;

int main(int argc, char const *argv[]) {
    Shape s1("ID 1");
    Shape s2("ID 2");
    Shape s3("ID 3");
    std::cout << Shape::count << std::endl;

    Ellipse e1("ID 1", 1.0, 2.0);
    Ellipse e2("ID 2", 2.0, 3.0);

    std::cout << Shape::count << std::endl;
    std::cout << Ellipse::count << std::endl;

    printf("----------------\n");

    Shape *s_ptr[] = {&s1, &s2, &s3, &e1, &e2};
    for (auto &s : s_ptr) {
        s->get_count();
    }

    return 0;
}