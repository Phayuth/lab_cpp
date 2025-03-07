#include <iostream>
// Abstract class is a class that cannot be instantiated.
// It is used to define an interface and force the derived class to implement the methods.
// use = 0 to make a method pure virtual.

class Shape {
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;

        virtual ~Shape() {
            printf("Shape is destroyed.\n");
        }
};

class Circle : public Shape {
    private:
        double r;

    public:
        Circle(double r) : r(r) {
        }

        double area() const override {
            return 3.14 * r * r;
        }

        double perimeter() const override {
            return 2 * 3.14 * r;
        }

        ~Circle() {
            printf("Circle is destroyed.\n");
        }
};

class Rectangle : public Shape {
    private:
        double width;
        double height;

    public:
        Rectangle(double width, double height) : width(width), height(height) {
        }

        double area() const override {
            return width * height;
        }

        double perimeter() const override {
            return 2 * (width + height);
        }

        ~Rectangle() {
            printf("Rectangle is destroyed.\n");
        }
};

int main(int argc, char const *argv[]) {
    // Shape *s = new Shape(); // error: cannot declare variable ‘s’ to be of abstract type ‘Shape’

    Circle c(2.0);
    Rectangle r(2.0, 3.0);

    Shape *s1 = &c;
    Shape *s2 = &r;

    std::cout << "Dynamic Type Name: " << typeid(*s1).name() << std::endl;
    std::cout << "Circle area: " << s1->area() << std::endl;
    std::cout << "Circle perimeter: " << s1->perimeter() << std::endl;

    std::cout << "Dynamic Type Name: " << typeid(*s2).name() << std::endl;
    std::cout << "Rectangle area: " << s2->area() << std::endl;
    std::cout << "Rectangle perimeter: " << s2->perimeter() << std::endl;

    return 0;
}