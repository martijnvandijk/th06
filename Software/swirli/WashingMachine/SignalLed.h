#ifndef WASHINGMACHINE_LED_H
#define WASHINGMACHINE_LED_H

#include "UARTHandler.h"

namespace WashingMachine{
    class SignalLed{
    public:
        /**
         * @brief Constructor, specify UARTHandler
         * 
         * @param uart The UARTHandler to be used for communicating with the emulator
         */
        SignalLed(UARTHandler &uart);

        /**
         * @brief Get the current status of the status LED
         * 
         * @param referenceUser The UARTUser that is calling the function (usually 'this' suffice)
         * @return true for on, false for off
         */
        bool getStatus(UARTUser *referenceUser);

        /**
         * @brief Toggle the status LED status
         * @details Turns the status LED on when off, and off when on.
         * 
         * @param referenceUser The UARTUser that is calling the function (usually 'this' suffice)
         */
        void toggle(UARTUser *referenceUser);
        
        /**
         * @brief Enable the status LED
         * 
         * @param referenceUser The UARTUser that is calling the function (usually 'this' suffice)
         */
        void enable(UARTUser *referenceUser);

        /**
         * @brief Disable the status LED
         * @details [long description]
         * 
         * @param referenceUser The UARTUser that is calling the function (usually 'this' suffice)
         */
        void disable(UARTUser *referenceUser);
    private:
        UARTHandler &uart;
    };
}
#endif