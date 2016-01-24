//
// Created by chiel on 21/01/16.
//

#include "WaitWaterLevelInstruction.h"

WaitWaterLevelInstruction::WaitWaterLevelInstruction(WaterLevelRegulator &water) :
		water(water) { }

void WaitWaterLevelInstruction::execute(
		WashingMachine::UARTUser *user,
		LogController &logController,
		bool doWait
) {
	if (doWait) {
		water.wait(user);
	}
}
