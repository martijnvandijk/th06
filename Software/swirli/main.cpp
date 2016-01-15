#include <iostream>

#include "WashingMachine/Motor.h"

#include "libserial.h"
#include "Protocol.h"
#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/UARTUser.h"
#define debug_task_logging_1
using namespace std;

class UARTTest : public WashingMachine::UARTUser {
public:
    UARTTest(WashingMachine::Motor &motor) :
            motor(motor),
            WashingMachine::UARTUser{98} {

    }

    void main() {
        while (true) {
            std::cout << "starting motor" << std::endl;
            motor.setRPM(100,this);
            std::cout << motor.getRPM(this) << std::endl;
            sleep(1 S);
            std::cout << "stopping motor" << std::endl;
            motor.setRPM(0,this);
            std::cout << motor.getRPM(this) << std::endl;
            sleep(1 S);
        }
    }


private:
    WashingMachine::Motor &motor;
};

int main() {
//    cout << "Hello, World!" << endl;
    LibSerial serial = LibSerial();
    serial.open("/dev/ttyAMA0", 9600);
    uint8_t commandOn[2];
    uint8_t commandOff[2];
    uint8_t commandStart[2];
    uint8_t commandTurn[2];

    commandOn[0]=SIGNAL_LED_REQ;
    commandOn[1]= ON_CMD;

    commandOff[0]=SIGNAL_LED_REQ;
    commandOff[1]=OFF_CMD;

    commandStart[0]=MACHINE_REQ;
    commandStart[1]=START_CMD;

    commandTurn[0]=SET_RPM_REQ;
    commandTurn[1]=0x00;

    serial.write(commandStart,2);
    serial.flush();
    WashingMachine::UARTHandler handler(serial);
    WashingMachine::Motor motor(handler);
    UARTTest test(motor);

    RTOS::run();
    return 0;
}

