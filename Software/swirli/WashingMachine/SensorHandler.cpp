#include "SensorHandler.h"
SensorHandler::SensorHandler():
		UARTUser(315,"SensorHandler") {
}

void SensorHandler::main() {
	for (;;) {
		for (WashingMachine::Observable *o : sensors) {
			o->poll(this);
		}
		sleep(100 MS);
	}
}

void SensorHandler::addSensor(WashingMachine::Observable *sensor) {
	sensors.push_back(sensor);
}
