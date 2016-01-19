#ifndef WASHINGMACHINE_DOOR_H
#define WASHINGMACHINE_DOOR_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "UARTHandler.h"
#include "UARTUser.h"

namespace WashingMachine{
    enum door_states_t {DOOR_OPENED, DOOR_UNLOCKED_CLOSED, DOOR_LOCKED};
    class Door{
    public:
        /**
         * @brief Constructor, specify UARTHandler instance
         * 
         * @param uart The UARTHandler to be used for communicating with the emulator
         */
         Door(UARTHandler &uart);
         /**
         * @brief getState Gets the current state of the heating unit
         * 
         * @param  referenceUser The UARTUser that is calling the function (usually 'this' suffices)
         * @return heatingunit_states_t Returns the enum DOOR_OPENED, DOOR_UNLOCKED_CLOSED or DOOR_LOCKED depending on wether the door is open, closed or locked.
         */
         door_states_t getState(UARTUser *referenceUser);
          /**
          * @brief set Sets the door to either the DOOR_LOCKED or the DOOR_UNLOCKED_CLOSED state.
          * @param state The state the door will be set to.
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
          void set(door_states_t state, UARTUser *referenceUser);

         /**
          * @brief toggle Toggles the door between the locked and unlocked state
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
          void toggle(UARTUser *referenceUser);

      private:
        UARTHandler uart;
    };
}
#endif