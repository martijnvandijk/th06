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
    void Pump::set(pump_states_t state, UARTUser *referenceUser){
    	UARTMessage command;
    	command.sender = referenceUser;
    	command.requestByte = PUMP_REQ;
    	if(state == PUMP_ON){
    		command.commandByte = ON_CMD;
    	}
    	else if(state == PUMP_OFF){
    		command.commandByte = OFF_CMD;
    	}
    	uart.sendMessage(command);
    }
    

    void Pump::toggle(UARTUser *referenceUser){
    	if(getState(referenceUser) == PUMP_ON){
			set(PUMP_OFF, referenceUser);
    	}
    	else if(getState(referenceUser) == PUMP_OFF){
			set(PUMP_ON, referenceUser);
    	}
    }
}