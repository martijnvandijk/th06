#ifndef WASHINGMACHINE_SENSORHANDLER_H
#define WASHINGMACHINE_SENSORHANDLER_H

#include "Observable.h"
#include "SensorListener.h"
#include "UARTUser.h"

/**
 * @brief RTOS task to poll the sensors and make them send updates to the subscribed listeners.
 */
class SensorHandler: public WashingMachine::UARTUser {
public:
	/**
	 * @brief Constructor
	 */
	SensorHandler();

	/**
	 * @brief Add a sensor to the handler
	 * 
	 * @param sensor The sensor to add to the handler.
	 */
	void addSensor(WashingMachine::Observable *sensor);

protected:
	virtual void main() override;

	std::vector<WashingMachine::Observable*> sensors;
};

#endif