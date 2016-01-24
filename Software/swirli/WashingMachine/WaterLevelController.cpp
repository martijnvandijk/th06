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
	for (int i{0};; i++) {
		RTOS::event event = RTOS::task::wait(targetWaterLevelUpdated + waterLevelUpdated);

		if (i >= 49) {
			std::cout << "water level is " << latestWaterLevel.read() << " target is " << targetWaterLevel.read() << std::endl;
			i = -1;
		}

		int diff{targetWaterLevel.read() - latestWaterLevel.read()};
		switch ((diff > 0) - (diff < 0)) {
			case -1:
				pump.set(WashingMachine::PUMP_ON, this);
				waterValve.set(WashingMachine::VALVE_CLOSED, this);
				break;
			case 0:
				pump.set(WashingMachine::PUMP_OFF, this);
				waterValve.set(WashingMachine::VALVE_CLOSED, this);

				if (event == waterLevelUpdated) {
					notifyAll();
				}
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
