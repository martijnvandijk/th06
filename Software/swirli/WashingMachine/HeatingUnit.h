#ifndef WASHINGMACHINE_HEATINGUNIT_H
#define WASHINGMACHINE_HEATINGUNIT_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "UARTHandler.h"
#include "UARTUser.h"

namespace WashingMachine{
    enum heatingunit_states_t {HEATINGUNIT_ON, HEATINGUNIT_OFF};
    class HeatingUnit{
    public:
        HeatingUnit(UARTHandler &uart);

        heatingunit_states_t getHeatingUnitState(UARTUser *referenceUser);
        void set_heatingunit(bool status, UARTUser *referenceUser);
        void toggle_heatingunit(UARTUser *referenceUser);

    private:
        UARTHandler &uart;
    };
}

#endif