//
// Created by chiel on 18/01/16.
//

#ifndef TEMPERATUREREGULATOR_H
#define TEMPERATUREREGULATOR_H

#include "../EventGenerator.h"

class TemperatureRegulator : public EventGenerator {
public:
	TemperatureRegulator(RTOS::task *parent): EventGenerator{parent} {}

	/**
	 * @brief set the desired temperature, the regulator will try to reach this
	 */
	virtual void setTemperature(int temperature) = 0;
	/**
	 * @brief get the temperature the regulator is trying to reach
	 */
	virtual int getTargetTemperature() = 0;
	/**
	 * @brief get the temperature the regulator is at right now
	 */
	virtual int getCurrentTemperature() = 0;
};

#endif //TEMPERATUREREGULATOR_H
