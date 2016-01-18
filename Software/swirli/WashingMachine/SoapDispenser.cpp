#include "SoapDispenser.h"
#include <stdint.h>
#include "UARTHandler.h"
#include "UARTUser.h"
namespace WashingMachine{

    SoapDispenser::SoapDispenser(UARTHandler &uart):
    uart(uart){
    }

    soapdispenser_states_t SoapDispenser::getSoapDispenserState(UARTUser *referenceUser){
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = SOAP_DISPENSER_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();

        switch(reply){
            case OPENED: return SOAP_OPEN; break;
            case CLOSED: return SOAP_CLOSED; break;
        }
    }

    void SoapDispenser::set_soapdispenser(bool status, UARTUser *referenceUser) {
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = SOAP_DISPENSER_REQ;
        if(status){
            command.commandByte = OPEN_CMD;
        }
        else{
            command.commandByte = CLOSE_CMD;
        }
        uart.sendMessage(command);
    }

    void SoapDispenser::toggle_soapdispenser (UARTUser *referenceUser) {
            if(getSoapDispenserState(referenceUser) == SOAP_OPEN){
                set_soapdispenser(false, referenceUser);
            }
            else if (getSoapDispenserState(referenceUser) != SOAP_CLOSED){
                set_soapdispenser(true, referenceUser);
            }
    }
}