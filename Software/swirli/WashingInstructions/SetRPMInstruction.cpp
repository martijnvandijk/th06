//
// Created by chiel on 17/01/16.
//

#include "SetRPMInstruction.h"

SetRPMInstruction::SetRPMInstruction(WashingMachine::Motor &motor, int rpm) :
		motor(motor),
		rpm{rpm} { }

void SetRPMInstruction::execute(WashingProgramRunner &runner,
                                LogController &logController,
                                bool doWait) {
	std::cout << "setting rpm: " << rpm << std::endl;
	motor.setRPM(rpm, &runner);
}
