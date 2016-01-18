#include "WaterLevelSensor.h"
#include "../libs/Protocol.h"
namespace WashingMachine{
	WaterLevelSensor::WaterLevelSensor(UARTHandler &uart):
    uart(uart){
    }

    int WaterLevelSensor::poll(UARTUser *referenceUser){
    	UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = TEMPERATURE_REQ;
        command.commandByte = 0xFF;
        uart.sendMessage(command);
        return referenceUser->getReplyPoolContents();
    }



}