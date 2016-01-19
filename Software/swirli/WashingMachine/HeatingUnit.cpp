#include "HeatingUnit.h"
#include <stdint.h>
namespace WashingMachine{
    HeatingUnit::HeatingUnit(UARTHandler &uart):
    uart(uart){
    }

    heatingunit_states_t HeatingUnit::getState(UARTUser *referenceUser){
        uint8_t *readBuf[2];

        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = HEATING_UNIT_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();
        if (reply == ON){
            return HEATINGUNIT_ON;
        }
        else if(reply == OFF){
            return HEATINGUNIT_OFF;
        }

    }
    void HeatingUnit::set(heatingunit_states_t state, UARTUser *referenceUser){
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = HEATING_UNIT_REQ;
        if(state == HEATINGUNIT_ON){
            command.commandByte = ON_CMD;
        }
        else if(state == HEATINGUNIT_OFF){
            command.commandByte = OFF_CMD;
        }
        uart.sendMessage(command);
    }
    

    void HeatingUnit::toggle(UARTUser *referenceUser){
        if(getState(referenceUser) == HEATINGUNIT_ON){
            set(HEATINGUNIT_OFF, referenceUser);
        }
        else if(getState(referenceUser) == HEATINGUNIT_OFF){
            set(HEATINGUNIT_ON, referenceUser);
        }
    }
}