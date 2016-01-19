#include <stdint.h>
#include "WaterValve.h"
#include "UARTHandler.h"
#include "UARTUser.h"
namespace WashingMachine{

    WaterValve::WaterValve(UARTHandler &uart):
    uart(uart){
    }

    watervalve_states_t WaterValve::getWaterValveState(UARTUser *referenceUser){
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = WATER_VALVE_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();

        switch(reply){
            case OPENED: return VALVE_OPEN; break;
            case CLOSED: return VALVE_CLOSED; break;
        }
    }

    void WaterValve::set(bool status, UARTUser *referenceUser) {
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = WATER_VALVE_REQ;
        if(status){
            command.commandByte = OPEN_CMD;
        }
        else{
            command.commandByte = CLOSE_CMD;
        }
        uart.sendMessage(command);
    }

    void WaterValve::toggle(UARTUser *referenceUser) {
            if(getWaterValveState(referenceUser) == VALVE_OPEN){
                set(false, referenceUser);
            }
            else if (getWaterValveState(referenceUser) != VALVE_CLOSED){
                set(true, referenceUser);
            }
    }
}