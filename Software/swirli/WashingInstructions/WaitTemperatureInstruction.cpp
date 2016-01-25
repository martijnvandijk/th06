//
// Created by chiel on 24/01/16.
//

#include "WaitTemperatureInstruction.h"

WaitTemperatureInstruction::WaitTemperatureInstruction(TemperatureRegulator &regulator) :
		regulator(regulator) {
}

void WaitTemperatureInstruction::execute(WashingProgramRunner &runner,
                                         LogController &logController,
                                         bool doWait) {
	if (doWait) {
		regulator.waitEvent(&runner);
	}
}
