#include <stdint.h>
#include "WaterValve.h"
#include "UARTHandler.h"
#include "UARTUser.h"
namespace WashingMachine{

    WaterValve::WaterValve(UARTHandler &uart):
    uart(uart){
    }

    watervalve_states_t WaterValve::getState(UARTUser *referenceUser){
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

    void WaterValve::set(watervalve_states_t state, UARTUser *referenceUser) {
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = WATER_VALVE_REQ;
        if(state == VALVE_OPEN){
            command.commandByte = OPEN_CMD;
        }
        else if(state == VALVE_CLOSED){
            command.commandByte = CLOSE_CMD;
        }
        uart.sendMessage(command);
    }

    void WaterValve::toggle(UARTUser *referenceUser) {
            if(getState(referenceUser) == VALVE_OPEN){
                set(VALVE_CLOSED, referenceUser);
            }
            else if (getState(referenceUser) != VALVE_CLOSED){
                set(VALVE_OPEN, referenceUser);
            }
    }
}