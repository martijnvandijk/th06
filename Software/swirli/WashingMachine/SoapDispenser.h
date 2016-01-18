#ifndef WASHINGMACHINE_SOAPDISPENSER_H
#define WASHINGMACHINE_SOAPDISPENSER_H
#include "../libs/Protocol.h"
#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
    enum soapdispenser_states_t {SOAP_OPEN, SOAP_CLOSED};
    class SoapDispenser{
    public:
        SoapDispenser(UARTHandler &uart);

        soapdispenser_states_t getSoapDispenserState(UARTUser *referenceUser);
        void set_soapdispenser(bool status, UARTUser *referenceUser);
        void toggle_soapdispenser(UARTUser *referenceUser);
    private:
        UARTHandler uart;

    };
}


#include "UARTUser.h"

namespace WashingMachine {
	class SoapDispenser;
}

#endif