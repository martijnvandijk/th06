//
// Created by chiel on 17/01/16.
//

#include "SetRPMInstruction.h"

SetRPMInstruction::SetRPMInstruction(WashingMachine::Motor &motor, int rpm):
        motor(motor),
        rpm{rpm}
{}

void SetRPMInstruction::execute(WashingMachine::UARTUser *user) {
	motor.setRPM(rpm, user);
}
