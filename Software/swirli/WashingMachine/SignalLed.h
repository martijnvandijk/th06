#ifndef WASHINGMACHINE_LED_H
#define WASHINGMACHINE_LED_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
    enum signalled_states_t{LED_ON, LED_OFF};
    class SignalLed{
    public:
        SignalLed(UARTHandler &uart);

        signalled_states_t getSignalLedStatus(UARTUser *referenceUser);
        void set_led(bool status, UARTUser *referenceUser);
        void toggle_led(UARTUser *referenceUser);
    private:
        UARTHandler &uart;
    };
}
#endif