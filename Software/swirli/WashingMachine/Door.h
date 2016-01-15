#ifndef WASHINGMACHINE_DOOR_H
#define WASHINGMACHINE_DOOR_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "../libs/libserial.h"
#include "UARTHandler.h"
#include "UARTUser.h"

namespace WashingMachine{
    enum door_states_t {DOOR_OPENED, DOOR_CLOSED, DOOR_LOCKED};
    class Door{
    public:
        Door(UARTHandler &uart);

        door_states_t getDoorState(UARTUser *referenceUser);
        void set_lock(bool status, UARTUser *referenceUser);
        void toggle_lock(UARTUser *referenceUser);

    private:
        UARTHandler uart;
    };
}
#endif