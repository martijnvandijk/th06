#include "HeatingUnit.h"
#include <stdint.h>
namespace WashingMachine{
    HeatingUnit::HeatingUnit(UARTHandler &uart):
    uart(uart){
    }

    heatingunit_states_t HeatingUnit::getHeatingUnitState(UARTUser *referenceUser){
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
    void HeatingUnit::set_heatingunit(bool status, UARTUser *referenceUser){
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = HEATING_UNIT_REQ;
        if(status){
            command.commandByte = ON_CMD;
        }
        else{
            command.commandByte = OFF_CMD;
        }
        uart.sendMessage(command);
    }
    

    void HeatingUnit::toggle_heatingunit(UARTUser *referenceUser){
        if(getHeatingUnitState(referenceUser) == HEATINGUNIT_ON){
            set_heatingunit(false, referenceUser);
        }
        else if(getHeatingUnitState(referenceUser) == HEATINGUNIT_OFF){
            set_heatingunit(true, referenceUser);
        }
    }
}