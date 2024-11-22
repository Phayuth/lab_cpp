#include <iostream>
#include <thread>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <vector>

using namespace ur_rtde;

int main(int argc, char *argv[]) {
    RTDEReceiveInterface rtde_receive("192.168.0.3");
    RTDEControlInterface rtde_control("192.168.0.3");

    std::vector<double> q = rtde_receive.getActualQ();

    for (size_t i = 0; i < q.size(); i++) {
        std::cout << q[i] << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::vector<double> qnew = q;
    qnew[5] = q[5] + 0.1;
    rtde_control.moveJ(qnew, 1.05, 1.4);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    rtde_control.stopJ(0.5); // Stop the movement before it reaches new_q
    rtde_control.stopScript(); // Stop the RTDE control script

    return 0;
}