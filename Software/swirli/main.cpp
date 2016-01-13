#include <iostream>
#include "libs/libserial.h"
#include "libs/Protocol.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
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

    serial.write(commandOn,2);
    std::cin.ignore();
    serial.write(commandOff,2);

    while(true){
        serial.write(commandTurn,2);
        commandTurn[1]+=0x01;
        std::cin.ignore();
    }

    serial.close();
    return 0;
}