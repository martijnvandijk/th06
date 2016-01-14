#include <stdint.h>
#include <iostream>
#include "Motor.h"
#include "../libs/Protocol.h"

WashingMachine::Motor::Motor(LibSerial &serial) :
    serialConnection(serial){

}

int WashingMachine::Motor::getRPM() {
    uint8_t *readBuf[2];
    serialConnection.writeChar(GET_RPM_REQ);
    serialConnection.read(readBuf, 2);

    return 0; //unfinished function
}

void WashingMachine::Motor::setRPM(int rpm) {
    uint8_t rpmbyte = abs(rpm)/25;
    std::cout<<rpmbyte<<std::endl;
    if(rpm < 0) {
        rpmbyte = rpmbyte | 0x80;
    }
    std::cout<<rpmbyte<<std::endl;
    serialConnection.writeChar(SET_RPM_REQ);
    serialConnection.writeChar(rpmbyte);
    uint8_t *readBuf[2];
    serialConnection.read(readBuf, 2);

}
