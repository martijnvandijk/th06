//
// Created by chiel on 18/01/16.
//

#include "SetDoorLockInstruction.h"
#include "../WashingMachine/UARTUser.h"

SetDoorLockInstruction::SetDoorLockInstruction(
		WashingMachine::Door &door,
		WashingMachine::DoorState lock
) :
		door(door),
		lock{lock} { }

void SetDoorLockInstruction::execute(
		WashingMachine::UARTUser *user,
		LogController &logController,
		bool doWait
) {
	door.set(lock, user);
}
