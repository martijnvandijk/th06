#ifndef WASHINGMACHINE_MOTOR_H
#define WASHINGMACHINE_MOTOR_H

#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
    /**
     * @brief Washing machine motor
     * @details Used for controlling the motor connected tot the drum.
     * 
     */
    class Motor{
    public:
    	/**
    	 * @brief Constructor, specify UARTHandler instance
    	 * 
    	 * @param uart The UARTHandler to be used for communicating with the emulator
    	 */
        Motor(UARTHandler &uart);

        /**
         * @brief Get the current RPM
         * 
         * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
         * @return The current RPM. Negative for opposite direction. Values will be -1600 to 1600.
         */
        int getRPM(UARTUser *referenceUser);

        /**
         * @brief Set the RPM
         * 
         * @param rpm The RPM to set the motor to. Valid values are -1600 to 1600.
         * @param referenceUser The UARTUser that is calling the function (usually 'this' suffces)
         */
        void setRPM(int rpm, UARTUser *referenceUser);
    private:
    UARTHandler &uart;

    };
}

#endif