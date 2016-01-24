#include <Protocol.h>
#include "SignalLed.h"
#include "UARTHandler.h"
namespace WashingMachine{
    SignalLed::SignalLed(WashingMachine::UARTHandler & uart):
            uart(uart){
    }

    SignalLedState SignalLed::getStatus(WashingMachine::UARTUser *referenceUser) {
        UARTMessage command;
        command.requestByte = SIGNAL_LED_REQ;
        command.commandByte = STATUS_CMD;
        command.sender = referenceUser;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();

        switch(reply){
            case ON: return LED_ON;
            case OFF: return LED_OFF;
        }
    }
    void SignalLed::set(SignalLedState status, UARTUser *referenceUser){
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = SIGNAL_LED_REQ;
        if(status){
            command.commandByte = ON_CMD;
        }
        else{
            command.commandByte = OFF_CMD;
        }

    }
    void SignalLed::toggle(UARTUser *referenceUser){
        if (getStatus(referenceUser) == LED_ON){
            set(LED_OFF, referenceUser);
        }
        else if(getStatus(referenceUser) == LED_OFF){
            set(LED_ON, referenceUser);
        }

    }
}