//
// Created by chiel on 18/01/16.
//

#ifndef SETDOORLOCKINSTRUCTION_H
#define SETDOORLOCKINSTRUCTION_H

#include "../WashingMachine/Door.h"
#include "WashingInstruction.h"

class SetDoorLockInstruction: public WashingInstruction {
public:
	SetDoorLockInstruction(WashingMachine::Door &door, WashingMachine::DoorState lock);

	virtual void execute(WashingMachine::UARTUser *user, LogController &logController) override;

private:
	WashingMachine::Door &door;
	WashingMachine::DoorState lock;
};


#endif //SETDOORLOCKINSTRUCTION_H
