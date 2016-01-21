#ifndef WASHINGMACHINE_SOAPDISPENSER_H
#define WASHINGMACHINE_SOAPDISPENSER_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
    // This is an enum class which handles the states the heating unit can be in.
    enum SoapDispenserState {
        SOAP_OPEN, // The soap dispenser is open
        SOAP_CLOSED // the soap dispenser is closed
     };
    class SoapDispenser{
    public:
        /**
       * @brief Constructor, specify UARTHandler instance
       * 
       * @param uart The UARTHandler to be used for communicating with the emulator
       */
        SoapDispenser(UARTHandler &uart);
        /**
         * @brief getState Gets the current state of the soap dispenser
         * 
         * @param  referenceUser The UARTUser that is calling the function (usually 'this' suffices)
         * @return heatingunit_states_t Returns the enum SOAP_OPEN or SOAP_CLOSED depending on wether the soap dispenser is open or closed
         */
        SoapDispenserState getState(UARTUser *referenceUser);
        /**
          * @brief set Sets the soap dipenser to either the open or closed state
          * @param state The state the soap dispenser will be set to
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
        void set(SoapDispenserState state, UARTUser *referenceUser);

         /**
          * @brief toggle Toggles the soap dispenser between the open and closed state.
          * @param referenceUser The UARTUser that is calling the function (usually 'this' suffices)
          */
        void toggle(UARTUser *referenceUser);
    private:
        UARTHandler &uart;

    };
}
#endif