#ifndef SWIRLI_WEBINTERFACEHANDLER_H
#define SWIRLI_WEBINTERFACEHANDLER_H

#include "WashingMachine/UARTUser.h"
#include "WashingMachine/UARTHandler.h"
#include "WebSocketPacket.h"
#include "WashingMachine/Motor.h"
#include "WashingMachine/Pump.h"
#include "WashingMachine/SignalLed.h"
#include "WashingMachine/Door.h"
#include "WashingMachine/HeatingUnit.h"
#include "WashingMachine/SoapDispenser.h"
#include "WashingMachine/TemperatureSensor.h"
#include "WashingMachine/WaterLevelSensor.h"
#include "WashingMachine/WaterValve.h"
#include "WashingMachine/WashingMachine.h"
//#include "WebSocketHandler.h"


class WebInterfaceHandler : WashingMachine::UARTUser {
public:
    WebInterfaceHandler(
            WashingMachine::WashingMachine &washingMachine
    );

    void handleRequest(std::shared_ptr<WebSocketPacket> &webSocketPacket);

private:
    RTOS::channel<std::shared_ptr<WebSocketPacket>, 128> InputQueue;
    WashingMachine::WashingMachine &washingMachine;

    void main();
};

#endif