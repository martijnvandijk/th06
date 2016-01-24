#ifndef SWIRLI_WEBINTERFACEHANDLER_H
#define SWIRLI_WEBINTERFACEHANDLER_H

#include <pRTOS.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <fstream>
#include <dirent.h>
#include "WebSocketPacket.h"
#include "WashingMachine/UARTUser.h"
#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/WashingMachine.h"
#include "SwirliListener.h"
#include "WashingMachine/TemperatureRegulator.h"
#include "WashingMachine/WaterLevelRegulator.h"
#include "WashingController.h"

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
            WashingController &washingController,
            SwirliListener &swirliListener
    );

private:
    WashingMachine::WashingMachine &washingMachine;
    TemperatureRegulator &temperatureRegulator;
    WaterLevelRegulator &waterLevelRegulator;
    WashingController &washingController;
    SwirliListener &listener;
    RTOS::timer timer;
    void main();
};

#endif