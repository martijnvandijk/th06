//
// Created by chiel on 21/01/16.
//

#include "WaitWaterLevelInstruction.h"

WaitWaterLevelInstruction::WaitWaterLevelInstruction(WaterLevelRegulator &water) :
		water(water) { }

void WaitWaterLevelInstruction::execute(WashingProgramRunner &runner, LogController &logController, bool doWait) {
	if (doWait) {
		water.waitEvent(&runner); // cannot check for stop due to inter-task flag restrictions
	}
}
