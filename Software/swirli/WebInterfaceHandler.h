#ifndef SWIRLI_WEBINTERFACEHANDLER_H
#define SWIRLI_WEBINTERFACEHANDLER_H

#include "WebSocketPacket.h"
#include "WashingMachine/UARTUser.h"
#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/WashingMachine.h"
#include "SwirliListener.h"
#include <pRTOS.h>

class WebInterfaceHandler : WashingMachine::UARTUser {
public:
    WebInterfaceHandler(
            WashingMachine::WashingMachine &washingMachine,
            SwirliListener &swirliListener
    );

private:
    WashingMachine::WashingMachine &washingMachine;
    SwirliListener &listener;
    RTOS::timer timer;
    void main();
};

#endif