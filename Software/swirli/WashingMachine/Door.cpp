#include <stdint.h>
#include "Door.h"
#include "UARTHandler.h"
#include "UARTUser.h"
namespace WashingMachine{

    Door::Door(UARTHandler &uart):
            uart(uart){
    }

    DoorState Door::getState(UARTUser *referenceUser) {
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = DOOR_LOCK_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();

        switch(reply){
            case LOCKED: return DOOR_LOCKED; break;
            case CLOSED: return DOOR_UNLOCKED_CLOSED; break;
            case OPENED: return DOOR_OPENED; break;
        }
    }

    void Door::set(DoorState state, UARTUser *referenceUser) {
        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = DOOR_LOCK_REQ;           
        if(state == DOOR_LOCKED){
            command.commandByte = LOCK_CMD;
        }
        else if(state == DOOR_UNLOCKED_CLOSED){
            command.commandByte = UNLOCK_CMD;
        }
        uart.sendMessage(command);
    }
    void Door::toggle(UARTUser *referenceUser) {
        if(getState(referenceUser) != DOOR_OPENED){
            if(getState(referenceUser) == DOOR_LOCKED){
                set(DOOR_UNLOCKED_CLOSED, referenceUser);
            }
            else{
                set(DOOR_UNLOCKED_CLOSED, referenceUser);
            }
        }
    }
}