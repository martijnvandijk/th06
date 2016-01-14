#include <stdint.h>
#include "Door.h"
namespace WashingMachine{

    Door::Door(LibSerial &serial):
        serialConnection(serial)
    {
    }

    door_states_t Door::getDoorState() {
        uint8_t *readBuf[2];
        serialConnection.writeChar(DOOR_LOCK_REQ);
        serialConnection.read(readBuf, 2);

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
        }
    }

    bool Door::set_lock() {
        return false;
    }

    bool Door::toggle_lock() {
        return false;
    }
}