#include "SoapDispenser.h"
#include <stdint.h>
#include "UARTHandler.h"
#include "UARTUser.h"
namespace WashingMachine{

    SoapDispenser::SoapDispenser(UARTHandler &uart):
    uart(uart){
    }

    SoapDispenserState SoapDispenser::getState(UARTUser *referenceUser){
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = SOAP_DISPENSER_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();

        switch(reply){
            case OPENED: return SOAP_OPEN;
            case CLOSED: return SOAP_CLOSED;
        }
    }

    void SoapDispenser::set(SoapDispenserState state, UARTUser *referenceUser) {
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = SOAP_DISPENSER_REQ;
        if(state == SOAP_OPEN){
            command.commandByte = OPEN_CMD;
        }
        else if(state == SOAP_CLOSED){
            command.commandByte = CLOSE_CMD;
        }
        uart.sendMessage(command);
    }

    void SoapDispenser::toggle(UARTUser *referenceUser) {
            if(getState(referenceUser) == SOAP_OPEN){
                set(SOAP_CLOSED, referenceUser);
            }
            else if (getState(referenceUser) != SOAP_CLOSED){
                set(SOAP_OPEN, referenceUser);
            }
    }
}