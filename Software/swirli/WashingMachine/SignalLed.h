#ifndef WASHINGMACHINE_LED_H
#define WASHINGMACHINE_LED_H

#include "UARTHandler.h"

namespace WashingMachine{
    class SignalLed{
    public:
        SignalLed(UARTHandler &uart);
        bool getStatus();
    };
}
#endif