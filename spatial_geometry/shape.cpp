#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Rectangle {
    public:
        float x;
        float y;
        float w;
        float h;

        Rectangle(float x, float y, float w, float h);
        ~Rectangle();

        void print_properties();
};

Rectangle::Rectangle(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Rectangle::print_properties() {
    printf("Rectangle Shape with x: %f, y: %f, w: %f, h: %f \n", x, y, w, h);
}

Rectangle::~Rectangle() {
}

bool check_rectangle(Rectangle rec1, Rectangle rec2) {
    if ((rec1.x + rec1.w >= rec2.x) && (rec1.x <= rec2.x + rec2.w) && (rec1.y + rec1.h >= rec2.y) && (rec1.y <= rec2.y + rec2.h)) {
        return true;
    }
    return false;
}

bool check_rectangle_refpass(Rectangle &rec1, Rectangle &rec2) {
    if ((rec1.x + rec1.w >= rec2.x) && (rec1.x <= rec2.x + rec2.w) && (rec1.y + rec1.h >= rec2.y) && (rec1.y <= rec2.y + rec2.h)) {
        return true;
    }
    return false;
}

int main() {
    Rectangle rec1(0.4, 1.3, 3.3, 4.4);
    rec1.print_properties();

    Rectangle rec2(0.4, 1.3, 2.2, 31.1);
    rec2.print_properties();

    bool res = check_rectangle(rec1, rec2);
    std::cout << res << std::endl;
    // 9873[ns]

    bool res2 = check_rectangle_refpass(rec1, rec2);
    std::cout << res2 << std::endl;
    // 10285[ns]

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;
    return 0;
}