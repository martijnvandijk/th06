#include <stdint.h>
#include <iostream>
#include "Motor.h"
#include "../libs/Protocol.h"
#include "UARTHandler.h"

WashingMachine::Motor::Motor(UARTHandler &uart) :
    uart(uart){

}


int WashingMachine::Motor::getRPM(UARTUser *referenceUser) {
    UARTMessage command;
    command.sender = referenceUser;
    command.requestByte = GET_RPM_REQ;
    command.commandByte = 0xFF;
    uart.sendMessage(command);
    uint8_t reply = referenceUser->getReplyPoolContents();
    if( reply & 0x80){
        reply &= 0x7F;
        return 0 - reply * 25;
    }
    return reply * 25;
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
