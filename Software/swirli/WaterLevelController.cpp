//
// Created by chiel on 20/01/16.
//

#include "WaterLevelController.h"

WaterLevelController::WaterLevelController(WashingMachine::Pump &pump, WashingMachine::WaterValve &waterValve):
		UARTUser{314, "WaterLevelController"},
		pump(pump),
		waterValve(waterValve),
		targetWaterLevel{"TargetWaterLevel"},
		targetWaterLevelUpdated{this, "TargetWaterLevelUpdated"},
		latestWaterLevel{"WaterLevel"},
		waterLevelUpdated{this, "WaterLevelUpdated"} {
}

void WaterLevelController::main() {
	for (;;) {
		RTOS::event event = wait(targetWaterLevelUpdated + waterLevelUpdated);

		int diff{targetWaterLevel.read() - latestWaterLevel.read()};
		switch ((diff > 0) - (diff < 0)) {
			case -1:
				pump.set(WashingMachine::PUMP_ON, this);
				waterValve.set(WashingMachine::VALVE_CLOSED, this);
				break;
			case 0:
				pump.set(WashingMachine::PUMP_OFF, this);
				waterValve.set(WashingMachine::VALVE_CLOSED, this);
				break;
			case 1:
				pump.set(WashingMachine::PUMP_OFF, this);
				waterValve.set(WashingMachine::VALVE_OPEN, this);
				break;
		}
	}
}

void WaterLevelController::setWaterLevel(int waterLevel) {
	targetWaterLevel.write(waterLevel);
	targetWaterLevelUpdated.set();
}

void WaterLevelController::update(int newVal) {
	latestWaterLevel.write(newVal);
	waterLevelUpdated.set();
}
