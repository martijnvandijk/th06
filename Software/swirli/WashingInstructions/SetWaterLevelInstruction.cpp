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

void SetWaterLevelInstruction::execute(
		WashingMachine::UARTUser *user,
		LogController &logController,
		bool doWait
) {
	waterRegulator.setWaterLevel(waterLevel);
}
