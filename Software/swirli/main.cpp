#include <iostream>
#include <thread>

#define debug_task_logging 1

#include "WashingMachine/Motor.h"
#include "Protocol.h"

#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/UARTUser.h"
#include "WashingMachine/WashingMachine.h"
#include "WebSocketHandler.h"
#include "WashingController.h"
#include "WashingMachine/TemperatureController.h"
#include "WashingMachine/WaterLevelController.h"

#define debug_task_logging_1

using namespace std;

class UARTTest : public WashingMachine::UARTUser {
public:
    UARTTest(WashingMachine::WashingMachine &washingMachine) :
            washingMachine(washingMachine),
            WashingMachine::UARTUser{98} {
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    void main() {
        while (true) {
            std::cout << "starting motor" << std::endl;
            washingMachine.getMotor().setRPM(100,this);
            std::cout << washingMachine.getMotor().getRPM(this) << std::endl;
            sleep(1 S);
            std::cout << "stopping motor" << std::endl;
            washingMachine.getMotor().setRPM(0,this);
            std::cout << washingMachine.getMotor().getRPM(this) << std::endl;
            sleep(1 S);
        }
    }
#pragma clang diagnostic pop


private:
    WashingMachine::WashingMachine &washingMachine;
};

int main() {

    float boat; //must be float, otherwise it sinks.

//    cout << "Hello, World!" << endl;
    LibSerial serial = LibSerial();
    serial.open("/dev/ttyAMA0", 9600);
//    uint8_t commandOn[2];
//    uint8_t commandOff[2];
//    uint8_t commandStart[2];
//    uint8_t commandTurn[2];
//
//    commandOn[0]=SIGNAL_LED_REQ;
//    commandOn[1]= ON_CMD;
//
//    commandOff[0]=SIGNAL_LED_REQ;
//    commandOff[1]=OFF_CMD;
//
//    commandStart[0]=MACHINE_REQ;
//    commandStart[1]=START_CMD;
//
//    commandTurn[0]=SET_RPM_REQ;
//    commandTurn[1]=0x00;

//    serial.write(commandStart,2);
//    serial.flush();


    WashingMachine::UARTHandler handler(serial);
    WashingMachine::WashingMachine washingMachine{handler};
    SensorHandler sensorHandler{};
    sensorHandler.addSensor(&washingMachine.getTemperatureSensor());
    sensorHandler.addSensor(&washingMachine.getWaterLevelSensor());
    TemperatureController temperatureController{washingMachine.getHeatingUnit()};
    WaterLevelController waterLevelController{washingMachine.getPump(), washingMachine.getWaterValve()};
    washingMachine.getTemperatureSensor().subscribe(&temperatureController);
    washingMachine.getWaterLevelSensor().subscribe(&waterLevelController);
//    UARTTest test(washingMachine);

    LogController logController{&std::cout};
    WashingController washingController{logController, handler, sensorHandler, washingMachine, temperatureController, waterLevelController};

    SwirliListener swirliListener;
    WebInterfaceHandler webInterfaceHandler(washingMachine, temperatureController, waterLevelController, washingController, swirliListener);
    WebSocketHandler wsh(2222, webInterfaceHandler, swirliListener);
    //doesn't seem to work :S
    std::thread websocketserver = wsh.spawnWebSocketHandler();

    std::cout << "starting RTOS" << std::endl;
    RTOS::run();
    websocketserver.join();

    return 0;
}

