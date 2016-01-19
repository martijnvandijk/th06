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
        /**
         * @brief Constructor, specify UARTHandler
         * 
         * @param uart The UARTHandler to be used for communicating with the emulator.
         */
        SignalLed(UARTHandler &uart);

        signalled_states_t getStatus(UARTUser *referenceUser);
        void set(signalled_states_t status, UARTUser *referenceUser);
        void toggle(UARTUser *referenceUser);

    private:
        UARTHandler &uart;
    };
}
#endif