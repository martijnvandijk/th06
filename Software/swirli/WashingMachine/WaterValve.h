#ifndef WASHINGMACHINE_WATERVALVE_H
#define WASHINGMACHINE_WATERVALVE_H

#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"
#include "../libs/Protocol.h"

namespace WashingMachine{
    // This is an enum class which handles the states the heating unit can be in.
    enum WaterValveState {
        VALVE_OPEN, // The water valve is open
        VALVE_CLOSED // the water valve is clsoed
    };
    class WaterValve{
    public:
        /**
       * @brief Constructor, specify UARTHandler instance
       * 
       * @param uart The UARTHandler to be used for communicating with the emulator
       */
       WaterValve(UARTHandler &uart);

         /**
         * @brief getState Gets the current state of the water valve
         * 
         * @param  referenceUser The UARTUser that is calling the function (usually 'this' suffices)
         * @return HeatingUnitState Returns the enum VALVE_OPEN or VALVE_CLOSED
         */
         WaterValveState getState(UARTUser *referenceUser);
        /**
          * @brief set Sets the hwater valve to either the open or closed state
          * @param state The state the water valve will be set to
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
          void set(WaterValveState state, UARTUser *referenceUser);
        /**
          * @brief toggle Toggles the water valve between the open and closed state.
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
          void toggle(UARTUser *referenceUser);
      private:
        UARTHandler &uart;
    };
}

#endif