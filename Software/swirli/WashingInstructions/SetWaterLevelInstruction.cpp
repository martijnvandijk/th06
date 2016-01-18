//
// Created by chiel on 18/01/16.
//

#include "SetWaterLevelInstruction.h"

SetWaterLevelInstruction::SetWaterLevelInstruction(WaterLevelRegulator &pump, int waterLevel):
		waterRegulator(waterRegulator),
        waterLevel{waterLevel}
{}

void SetWaterLevelInstruction::execute(WashingMachine::UARTUser *user) {
	waterRegulator.setWaterLevel(waterLevel);
}
