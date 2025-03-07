#include <iostream>
#include <memory>
#include <string>
// when override overloads function, it hide ALL the overloads function in the base class.
// to enable it back, we need to override it one by one.

class Shape {
    public:
        std::string desc;

        Shape(const std::string &desc) : desc(desc) {
        }

        virtual void draw() const {
            printf("Shape [%s] is drawn.\n", desc.c_str());
        }

        virtual void draw(int color) const {
            printf("Shape [%s] is drawn with color id %i.\n", desc.c_str(), color);
        }
};

class Oval : public Shape {
    public:
        double xr;
        double yr;

        Oval(const std::string &desc, double xr, double yr) : Shape(desc), xr(xr), yr(yr) {
        }

        virtual void draw() const override {
            printf("Oval [%s] is drawn. Additional Info: %f, %f \n", desc.c_str(), xr, yr);
        }

        virtual void draw(int color) const override { // override one by one to enable it back
            printf("Oval [%s] is drawn with color id %i. Additional Info: %f, %f \n", desc.c_str(), color, xr, yr);
        }

        // this method will not participate in the polymorphism as the original class has no idea there is a new method in the new class
        virtual void draw(int color, std::string &name) const {
            printf("Oval [%s] is drawn with color id %i. Additional Info: %f, %f \n", desc.c_str(), color, xr, yr);
        }
};

class Circle : public Oval {
    public:
        double r;

        Circle(const std::string &des, double r) : Oval(des, r, r), r(r) {
        }

        virtual void draw() const override {
            printf("Circle [%s] is drawn. Addtional Info: %f \n", desc.c_str(), r);
        }
};

void draw_all(Shape *s) {
    s->draw();
}

int main(int argc, char const *argv[]) {
    Shape s1("ID 1");
    s1.draw();
    s1.draw(2);

    Oval o1("ID 2", 1.2, 3.1);
    o1.draw();
    o1.draw(4); // compiler error, because the derived class is overriding BOTH overload method in the original class.

    Shape* s1_ptr = &o1;
    // s1_ptr->draw(2, "color red"); // compiler error, method is not known to the original class.

    return 0;
}
