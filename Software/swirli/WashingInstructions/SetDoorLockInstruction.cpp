//
// Created by chiel on 18/01/16.
//

#include "SetDoorLockInstruction.h"
#include "../WashingMachine/UARTUser.h"

SetDoorLockInstruction::SetDoorLockInstruction(WashingMachine::Door &door, WashingMachine::door_states_t lock):
		door(door),
        lock{lock}
{}

void SetDoorLockInstruction::execute(WashingMachine::UARTUser *user) {
	door.set(lock, user);
}
