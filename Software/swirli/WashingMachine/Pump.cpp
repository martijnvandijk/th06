#include <stdint.h>
#include "Pump.h"
namespace WashingMachine{
	 Pump::Pump(UARTHandler &uart):
	 uart(uart){
	 }

    pump_states_t Pump::getState(UARTUser *referenceUser){
    	uint8_t *readBuf[2];

        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = PUMP_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);
        uint8_t reply = referenceUser->getReplyPoolContents();
        if (reply == ON){
        	return PUMP_ON;
        }
        else if(reply == OFF){
        	return PUMP_OFF;
        }

    }
    void Pump::set(bool status, UARTUser *referenceUser){
    	UARTMessage command;
    	command.sender = referenceUser;
    	command.requestByte = PUMP_REQ;
    	if(status){
    		command.commandByte = ON_CMD;
    	}
    	else{
    		command.commandByte = OFF_CMD;
    	}
    	uart.sendMessage(command);
    }
    

    void Pump::toggle(UARTUser *referenceUser){
    	if(getState(referenceUser) == PUMP_ON){
			set(false, referenceUser);
    	}
    	else if(getState(referenceUser) == PUMP_OFF){
			set(true, referenceUser);
    	}
    }
}