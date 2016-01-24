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

class WebInterfaceHandler : WashingMachine::UARTUser {
public:
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