#ifndef WASHINGMACHINE_SENSORHANDLER_H
#define WASHINGMACHINE_SENSORHANDLER_H

#include "Observable.h"
#include "SensorListener.h"
#include "UARTUser.h"

class SensorHandler: public WashingMachine::UARTUser {
public:
	SensorHandler();

	void addSensor(WashingMachine::Observable *sensor);

protected:
	virtual void main() override;

	std::vector<WashingMachine::Observable*> sensors;
};

#endif