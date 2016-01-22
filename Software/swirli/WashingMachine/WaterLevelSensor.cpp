#include "WaterLevelSensor.h"
#include "../libs/Protocol.h"
namespace WashingMachine{
	WaterLevelSensor::WaterLevelSensor(UARTHandler &uart):
			uart(uart) {
    }

    int WaterLevelSensor::poll(UARTUser *referenceUser){
    	UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = WATER_LEVEL_REQ;
        command.commandByte = 0xFF;
        uart.sendMessage(command);

	    int newVal{referenceUser->getReplyPoolContents()};
	    updateAll(newVal);
        return newVal;
    }

}