//
// Created by chiel on 20/01/16.
//

#include "TemperatureController.h"

TemperatureController::TemperatureController(WashingMachine::HeatingUnit &heat):
		UARTUser{314, "TemperatureController"},
		heat(heat),
		targetTemperature{"TargetTemperature"},
		targetTemperatureUpdated{this, "TargetTemperatureUpdated"},
		latestTemperature{"Temperature"},
		temperatureUpdated{this, "TemperatureUpdated"} {
}

void TemperatureController::main() {
	for (int i{0};; i++) {
		wait(targetTemperatureUpdated + temperatureUpdated);

		if (i >= 49) {
			std::cout << "temperature is " << latestTemperature.read() << " target is " << targetTemperature.read() << std::endl;
			i = -1;
		}

		int diff{targetTemperature.read() - latestTemperature.read()};
		if (diff > 0) {
			heat.set(WashingMachine::HEATINGUNIT_ON, this);
		} else {
			heat.set(WashingMachine::HEATINGUNIT_OFF, this);

			if (diff == 0) {
				notifyAll();
			}
		}
	}
}

void TemperatureController::setTemperature(int Temperature) {
	targetTemperature.write(Temperature);
	targetTemperatureUpdated.set();
}

void TemperatureController::update(int newVal) {
	latestTemperature.write(newVal);
	temperatureUpdated.set();
}

int TemperatureController::getTargetTemperature() {
	return targetTemperature.read();
}

int TemperatureController::getCurrentTemperature() {
	return latestTemperature.read();
}
