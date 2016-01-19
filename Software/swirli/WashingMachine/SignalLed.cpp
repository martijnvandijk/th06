#include <Protocol.h>
#include "SignalLed.h"
#include "UARTHandler.h"
namespace WashingMachine{
    SignalLed::SignalLed(WashingMachine::UARTHandler & uart):
    uart(uart){
    }

    signalled_states_t SignalLed::getStatus(WashingMachine::UARTUser *referenceUser) {
        UARTMessage command;
        command.requestByte = SIGNAL_LED_REQ;
        command.commandByte = STATUS_CMD;
        command.sender = referenceUser;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();

        switch(reply){
            case ON: return LED_ON; break;
            case OFF: return LED_OFF; break;
        }
    }
    void SignalLed::set_led(bool status, UARTUser *referenceUser){
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
    void SignalLed::toggle_led(UARTUser *referenceUser){
        if (getStatus(referenceUser) == LED_ON){
            set_led(false, referenceUser);
        }
        else if(getStatus(referenceUser) == LED_OFF){
            set_led(true, referenceUser);
        }

    }
}