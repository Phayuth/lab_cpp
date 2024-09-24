#include <cmath>
#include <cstdio>
#include <iostream>

class DifferentialDriveRobot {
    private:
        double blength;
        double wradius;

    public:
        double x;
        double y;
        double yaw;

        DifferentialDriveRobot(double blength, double wradius, double x, double y, double yaw);
        ~DifferentialDriveRobot();

        void set_pose(double x, double y, double yaw);

        void fkin_ex(double v, double w, double Ts);
        void fkin_in(double wr, double wl, double Ts);

        void prt_pose(void);
};

DifferentialDriveRobot::DifferentialDriveRobot(double blength, double wradius, double x, double y, double yaw) {
    this->blength = blength;
    this->wradius = wradius;

    set_pose(x, y, yaw);
}

DifferentialDriveRobot::~DifferentialDriveRobot() {
}

void DifferentialDriveRobot::set_pose(double x, double y, double yaw) {
    this->x = x;
    this->y = y;
    this->yaw = yaw;
}

void DifferentialDriveRobot::fkin_ex(double v, double w, double Ts) {
    x += v * cos(yaw) * Ts;
    y += v * sin(yaw) * Ts;
    yaw += w * Ts;
}

void DifferentialDriveRobot::fkin_in(double wr, double wl, double Ts) {
    double v = (wradius / 2.0) * (wr + wl);
    double w = (wradius / blength) * (wr - wl);
    fkin_ex(v, w, Ts);
}

void DifferentialDriveRobot::prt_pose(void) {
    printf("pose | x:%f, y:%f, yaw:%f \n", x, y, yaw);
}

int main(int argc, char const *argv[]) {
    DifferentialDriveRobot robot(.5, .1, .0, .0, .0);

    double t(0.0);
    while (t < 5.0) {
        robot.fkin_ex(.2, .0, .01);
        robot.prt_pose();
        t += .01;
    }

    return 0;
}
