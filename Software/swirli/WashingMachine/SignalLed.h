#ifndef WASHINGMACHINE_LED_H
#define WASHINGMACHINE_LED_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
    enum SignalLedState {LED_ON, LED_OFF};
    class SignalLed{
    public:
        /**
         * @brief Constructor, specify UARTHandler
         * 
         * @param uart The UARTHandler to be used for communicating with the emulator.
         */
        SignalLed(UARTHandler &uart);

        SignalLedState getStatus(UARTUser *referenceUser);
        void set(SignalLedState status, UARTUser *referenceUser);
        void toggle(UARTUser *referenceUser);

    private:
        UARTHandler &uart;
    };
}
#endif