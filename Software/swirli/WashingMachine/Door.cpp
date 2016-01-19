#include <stdint.h>
#include "Door.h"
#include "UARTHandler.h"
#include "UARTUser.h"
namespace WashingMachine{

    Door::Door(UARTHandler &uart):
    uart(uart){
    }

    door_states_t Door::getDoorState(UARTUser *referenceUser) {
        uint8_t *readBuf[2];

        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = DOOR_LOCK_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();

        switch(reply){
            case LOCKED: return DOOR_LOCKED; break;
            case CLOSED: return DOOR_CLOSED; break;
            case OPENED: return DOOR_OPENED; break;
        }
    }

    void Door::setLock(bool status, UARTUser *referenceUser) {
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = DOOR_LOCK_REQ;           
        if(status){
            command.commandByte = LOCK_CMD;
        }
        else{
            command.commandByte = UNLOCK_CMD;
        }
        uart.sendMessage(command);
    }

    void Door::toggleLock(UARTUser *referenceUser) {
        if(getDoorState(referenceUser) == DOOR_CLOSED){
            if(getDoorState(referenceUser) == DOOR_LOCKED){
                setLock(false, referenceUser);
            }
            else if (getDoorState(referenceUser) != DOOR_LOCKED){
                setLock(true, referenceUser);
            }
        }
    }
}