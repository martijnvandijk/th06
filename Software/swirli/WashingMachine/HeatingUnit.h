#ifndef WASHINGMACHINE_HEATINGUNIT_H
#define WASHINGMACHINE_HEATINGUNIT_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "UARTHandler.h"
#include "UARTUser.h"

namespace WashingMachine{
    // This is an enum class which handles the states the heating unit can be in.
  enum heatingunit_states_t {
        HEATINGUNIT_ON, // The heating unit is on
        HEATINGUNIT_OFF // the heating unit is off
      };
      class HeatingUnit{
      public:
       /**
       * @brief Constructor, specify UARTHandler instance
       * 
       * @param uart The UARTHandler to be used for communicating with the emulator
       */
       HeatingUnit(UARTHandler &uart);
        /**
         * @brief getState Gets the current state of the heating unit
         * 
         * @param  referenceUser The UARTUser that is calling the function (usually 'this' suffices)
         * @return heatingunit_states_t Returns the enum HEATINGUNIT_ON or HEATINGUNIT_OFF depending on wether the heatingunit is on or off.
         */
         heatingunit_states_t getState(UARTUser *referenceUser);
         /**
          * @brief set Sets the heating unit to either the on or off state.
          * @param state The state the heating unit will be set to.
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
          void set(heatingunit_states_t state, UARTUser *referenceUser);
         /**
          * @brief toggle Toggles the heating unit between the on and off state.
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
          void toggle(UARTUser *referenceUser);

        private:
          UARTHandler &uart;
        };
      }

#endif