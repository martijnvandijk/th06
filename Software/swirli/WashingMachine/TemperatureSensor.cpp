#include "TemperatureSensor.h"
#include "../libs/Protocol.h"
namespace WashingMachine{
	TemperatureSensor::TemperatureSensor(UARTHandler &uart):
    uart(uart){
    }

    int TemperatureSensor::poll(UARTUser *referenceUser){
    	UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = TEMPERATURE_REQ;
        command.commandByte = 0xFF;
        uart.sendMessage(command);
        return referenceUser->getReplyPoolContents();
    }

}