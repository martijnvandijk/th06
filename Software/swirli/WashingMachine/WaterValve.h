#ifndef WASHINGMACHINE_WATERVALVE_H
#define WASHINGMACHINE_WATERVALVE_H

#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"
#include "../libs/Protocol.h"

namespace WashingMachine{
    enum watervalve_states_t {VALVE_OPEN, VALVE_CLOSED};
    class WaterValve{
    public:
        WaterValve(UARTHandler &uart);

        watervalve_states_t getWaterValveState(UARTUser *referenceUser);
        void set_watervalve(bool status, UARTUser *referenceUser);
        void toggle_watervalve(UARTUser *referenceUser);
    private:
    UARTHandler uart;

    };
}

#endif