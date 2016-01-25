//
// Created by chiel on 18/01/16.
//

#include "SetWaterLevelInstruction.h"

SetWaterLevelInstruction::SetWaterLevelInstruction(
		WaterLevelRegulator &waterRegulator,
		int waterLevel
) :
		waterRegulator(waterRegulator),
		waterLevel{waterLevel} { }

void SetWaterLevelInstruction::execute(WashingProgramRunner &runner,
                                       LogController &logController,
                                       bool doWait) {
	std::cout << "setting waterLevel: " << waterLevel << std::endl;
	waterRegulator.setWaterLevel(waterLevel);
}
