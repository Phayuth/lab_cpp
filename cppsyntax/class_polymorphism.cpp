#include <iostream>
#include <memory>
#include <string>

class Shape {
    public:
        std::string desc;

        Shape(const std::string &desc) : desc(desc) {
        }

        // use virtual to allow override (dynamically binding)
        virtual void draw() const {
            printf("Shape [%s] is drawn.\n", desc.c_str());
        }
};

class Oval : public Shape {
    public:
        double xr;
        double yr;

        Oval(const std::string &desc, double xr, double yr)
            : Shape(desc), xr(xr), yr(yr) {
        }

        virtual void
        draw() const override { // specify override to make sure the method is
                                // override from the base class by the compiler
            printf("Oval [%s] is drawn. Additional Info: %f, %f \n",
                   desc.c_str(),
                   xr,
                   yr);
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

    Oval o1("ID 2", 2.1, 4.1);
    o1.draw();

    Circle c1("ID 3", 1.1);
    c1.draw();

    // Base pointer
    // static binding
    // point to shape
    Shape *shape_ptr = &s1;
    shape_ptr->draw();

    // point to oval
    shape_ptr = &o1;
    shape_ptr->draw();

    // point to circle
    shape_ptr = &c1;
    shape_ptr->draw();

    // Base reference
    // The problem is that assigning derived class objects to a base class
    // reference slices the object, losing the derived class information because
    // not enough space. To fix this, you should use pointers instead of references
    // for polymorphic behavior. DONT USE THIS. Shape &shape_ref = s1;
    // shape_ref.draw();
    // shape_ref = o1;
    // shape_ref.draw();
    // shape_ref = c1;
    // shape_ref.draw();

    draw_all(&s1);
    draw_all(&o1);
    draw_all(&c1);

    draw_all(shape_ptr);

    Shape sliceoff_data[]{s1, o1, c1}; // this will slice off your data and lost
                                       // forever. because we have implicit copy.

    Shape *shape_col[]{&s1, &o1, &c1};
    for (Shape *s_ptr : shape_col) {
        s_ptr->draw();
    }

    // using smart pointer
    std::shared_ptr<Shape> shape_smartptr[]{std::make_shared<Shape>(s1),
                                            std::make_shared<Oval>(o1),
                                            std::make_shared<Circle>(c1)};
    for (std::shared_ptr<Shape> s_ptr : shape_smartptr) {
        s_ptr->draw();
    }

    return 0;
}
