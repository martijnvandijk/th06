#include <stdint.h>
#include <iostream>
#include "Motor.h"
#include "../libs/Protocol.h"
#include "UARTHandler.h"

WashingMachine::Motor::Motor(UARTHandler &uart) :
    uart (uart){

}

int WashingMachine::Motor::getRPM() {
    uint8_t *readBuf[2];
//    serialConnection.writeChar(GET_RPM_REQ);
//    serialConnection.read(readBuf, 2);

    return 0; //unfinished function
}

void WashingMachine::Motor::setRPM(int rpm, UARTUser *referenceUser) {
    uint8_t rpmbyte = abs(rpm)/25;
    if(rpm < 0){
        rpmbyte |= 0x80;
    }
    UARTMessage command;
    command.sender = referenceUser;
    command.requestByte = SET_RPM_REQ;
    command.commandByte = rpmbyte;
    uart.sendMessage(command);
}

//void WashingMachine::Motor::receiveReply(uint8_t replyByte) {
//    replyPool.write(replyByte);
//}

/*void WashingMachine::Motor::setRPM(int rpm, ) {
    uint8_t rpmbyte = abs(rpm)/25;
    std::cout<<rpmbyte<<std::endl;
    if(rpm < 0) {
        rpmbyte = rpmbyte | 0x80;
    }
    serialConnection.writeChar(SET_RPM_REQ);
    serialConnection.writeChar(rpmbyte);
    uint8_t *readBuf[2];
    serialConnection.read(readBuf, 2);

}

*/