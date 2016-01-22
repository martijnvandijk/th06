#ifndef WASHINGMACHINE_PUMP_H
#define WASHINGMACHINE_PUMP_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "../libs/libserial.h"
#include "UARTHandler.h"
#include "UARTUser.h"

namespace WashingMachine{
    // This is an enum class which handles the states the heating unit can be in.
    enum PumpState {
        PUMP_ON, // The pump is on
         PUMP_OFF // The pump is off
     };
    class Pump{
    public:
        /**
         * @brief Constructor, specify UARTHandler instance
         * 
         * @param uart The UARTHandler to be used for communicating with the emulator
         */
        Pump(UARTHandler &uart);

       /**
         * @brief getState Gets the current state of the pump
         * 
         * @param  referenceUser The UARTUser that is calling the function (usually 'this' suffices)
         * @return PumpState Returns the enum PUMP_ON or PUMP_OFF depending on wether the pump is on or off.
         */
       PumpState getState(UARTUser *referenceUser);

        /**
          * @brief set Sets the pump to either the on or off state.
          * @param state The state the pump will be set to.
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
        void set(PumpState state, UARTUser *referenceUser);

        /**
          * @brief toggle Toggles the pump between the on and off state.
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
        void toggle(UARTUser *referenceUser);

    private:
        UARTHandler &uart;
    };
}

#endif