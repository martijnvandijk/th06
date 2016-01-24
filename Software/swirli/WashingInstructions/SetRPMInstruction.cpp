//
// Created by chiel on 17/01/16.
//

#include "SetRPMInstruction.h"

SetRPMInstruction::SetRPMInstruction(WashingMachine::Motor &motor, int rpm) :
		motor(motor),
		rpm{rpm} { }

void SetRPMInstruction::execute(
		WashingMachine::UARTUser *user,
		LogController &logController,
		bool doWait
) {
	std::cout << "setting rpm: " << rpm << std::endl;
	motor.setRPM(rpm, user);
}
