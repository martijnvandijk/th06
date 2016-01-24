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

/**
 * @brief Used to exchange data between the websockethandler and the RTOS.
 * 
 */
class WebInterfaceHandler : WashingMachine::UARTUser {
public:
    /**
     * @brief Constructor
     * 
     * @param washingMachine The washing machine object for gaining access to the boundary objects.
     * @param temperatureRegulator The temperature regulator. Passed on to the washing controller.
     * @param waterLevelRegulator The water level regulator. Passed on to the washing controller.
     * @param swirliListener The listener object to get websocket packets from.
     */
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