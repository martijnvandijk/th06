//
// Created by chiel on 18/01/16.
//

#ifndef SETDOORLOCKINSTRUCTION_H
#define SETDOORLOCKINSTRUCTION_H

#include "../WashingInstruction.h"
#include "../WashingMachine/Door.h"

class SetDoorLockInstruction: public WashingInstruction {
public:
	SetDoorLockInstruction(WashingMachine::Door &door, WashingMachine::door_states_t lock);

	virtual void execute(WashingMachine::UARTUser *user) override;

private:
	WashingMachine::Door &door;
	WashingMachine::door_states_t lock;
};


#endif //SETDOORLOCKINSTRUCTION_H
