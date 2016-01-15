#include <stdint.h>
#include "Door.h"
#include "UARTHandler.h"
namespace WashingMachine{

    Door::Door(UARTHandler &uart):
    uart{uart}{
    }

    door_states_t Door::getDoorState(UARTUser *referenceUser) {
        uint8_t *readBuf[2];

        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = DOOR_LOCK_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);

        /*ADD RECEIVE REPLY HERE TO GET DOOR STATUS
        if(*readBuf[0] == ( REPLY_BIT | DOOR_LOCK_REQ)){
            switch(*readBuf[1]){
                case LOCKED:
                    return DOOR_LOCKED;
                    break;
                case CLOSED:
                    return DOOR_CLOSED;
                    break;
                case OPENED:
                    return DOOR_OPENED;
                    break;
            }
        }*/
    }

    void Door::set_lock(bool status, UARTUser *referenceUser) {
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

    void Door::toggle_lock(UARTUser *referenceUser) {
        if(getDoorState(referenceUser) == DOOR_LOCKED && getDoorState(referenceUser) == DOOR_CLOSED){
            set_lock(false, referenceUser);
        }
        else if (getDoorState(referenceUser) == DOOR_CLOSED && getDoorState(referenceUser) != DOOR_LOCKED){
            set_lock(true, referenceUser);
        }
    }
}