#ifndef SWIRLI_WEBINTERFACEHANDLER_H
#define SWIRLI_WEBINTERFACEHANDLER_H

#include "WebSocketPacket.h"
#include "WashingMachine/UARTUser.h"
#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/WashingMachine.h"
#include "SwirliListener.h"
#include "WashingMachine/TemperatureRegulator.h"
#include "WashingMachine/WaterLevelRegulator.h"
#include <pRTOS.h>

class WebInterfaceHandler : WashingMachine::UARTUser {
public:
    WebInterfaceHandler(
            WashingMachine::WashingMachine &washingMachine,
            TemperatureRegulator &temperatureRegulator,
            WaterLevelRegulator &waterLevelRegulator,
            SwirliListener &swirliListener
    );

private:
    WashingMachine::WashingMachine &washingMachine;
    TemperatureRegulator &temperatureRegulator;
    WaterLevelRegulator &waterLevelRegulator;
    SwirliListener &listener;
    RTOS::timer timer;
    void main();
};

#endif