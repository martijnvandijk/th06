#ifndef WASHINGMACHINE_LED_H
#define WASHINGMACHINE_LED_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"

/**
 * WashingMachine Namespace, contains all boundary objects.
 */
namespace WashingMachine{
    
    /// Enum to describe the LED state.
    enum SignalLedState{
        LED_ON, ///< The LED is on.
        LED_OFF ///< The LED is off.
    };
    
    /**
     * @brief A signal LED
     * @details Can be on, can be off. Can be used to send simple messages to the user.
     * 
     */
    class SignalLed{
    public:
        /**
         * @brief Constructor, specify UARTHandler
         * 
         * @param uart The UARTHandler to be used for communicating with the emulator.
         */
        SignalLed(UARTHandler &uart);

        /**
         * @brief Get the LED status
         * 
         * @param referenceUser The UARTUser calling this method. Usually 'this' suffices.
         * @return The
         */
        SignalLedState getStatus(UARTUser *referenceUser);

        /**
         * @brief Set the LED status
         * 
         * @param status The status to set the LED to
         * @param referenceUser The UARTUser calling this method.
         */
        void set(SignalLedState status, UARTUser *referenceUser);

        /**
         * @brief Toggle the LED
         * @details Turn it off if on, turn it on if off.
         * 
         * @param referenceUser The UARTUser calling this method.
         */
        void toggle(UARTUser *referenceUser);

    private:
        /**
         * The UARTHandler used to send messages to the hardware.
         */
        UARTHandler &uart;
    };
}
#endif