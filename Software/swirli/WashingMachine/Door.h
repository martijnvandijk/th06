#ifndef WASHINGMACHINE_DOOR_H
#define WASHINGMACHINE_DOOR_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "../libs/libserial.h"

namespace WashingMachine{
    enum door_states_t {DOOR_OPENED, DOOR_CLOSED, DOOR_LOCKED};
    class Door{
    public:
        Door(LibSerial &serial);

        door_states_t getDoorState();
        void set_lock(bool status);
        void toggle_lock();

    private:
        UARTHandler &uart;


    };
}
#endif