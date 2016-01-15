#include <Protocol.h>
#include "SignalLed.h"
#include "UARTHandler.h"

WashingMachine::SignalLed::SignalLed(WashingMachine::UARTHandler & uart):
uart(uart){

}

bool WashingMachine::SignalLed::getStatus(WashingMachine::UARTUser *referenceUser) {
    UARTMessage command;
    command.requestByte = SIGNAL_LED_REQ;
    command.commandByte = STATUS_CMD;
    command.sender = referenceUser;
}

void WashingMachine::SignalLed::toggle(WashingMachine::UARTUser *referenceUser) {

}

void WashingMachine::SignalLed::enable(WashingMachine::UARTUser *referenceUser) {

}

void WashingMachine::SignalLed::disable(WashingMachine::UARTUser *referenceUser) {

}
