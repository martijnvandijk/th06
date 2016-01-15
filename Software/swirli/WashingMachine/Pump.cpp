#include <stdint.h>
#include "Pump.h"
namespace washingMachine{
	 Pump::Pump(UARTHandler &uart):
	 uart{uart}{
	 }

    pump_states_t Pump::getPumpState(UARTUser *referenceUser){
    	uint8_t *readBuf[2];

        UARTMessage command;
        command.sender = referenceUser;
        command.requestByte = PUMP_REQ;
        command.commandByte = STATUS_CMD;
        uart.sendMessage(command);

        //Add receive reply here
        // returns PUMP_ON / PUMP_OFF

    }
    void Pump::set_pump(bool status, UARTUser *referenceUser){
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
    

    void Pump::toggle_pump(UARTUser *referenceUser){
    	if(getPumpState(referenceUser) == PUMP_ON){
    		set_pump(false, referenceUser);
    	}
    	else if(getPumpState(referenceUser) == PUMP_OFF){
    		set_pump(true, referenceUser);
    	}
    }
}