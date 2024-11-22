#include <ur_rtde/rtde_control_interface.h>
using namespace ur_rtde;

int main(int argc, char *argv[]) {
    RTDEControlInterface rtde_control("192.168.0.3");

    // Parameters
    std::vector<double> speed = {0, 0, -0.100, 0, 0, 0};
    rtde_control.moveUntilContact(speed);
    rtde_control.stopScript();
    return 0;
}
