#ifndef WASHINGMACHINE_PUMP_H
#define WASHINGMACHINE_PUMP_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "../libs/libserial.h"
#include "UARTHandler.h"
#include "UARTUser.h"

namespace WashingMachine{
    enum pump_states_t {PUMP_ON, PUMP_OFF};
    class Pump{
    public:
        Pump(UARTHandler &uart);

        pump_states_t getState(UARTUser *referenceUser);
        void set(bool status, UARTUser *referenceUser);
        void toggle(UARTUser *referenceUser);

    private:
        UARTHandler &uart;
    };
}

#endif