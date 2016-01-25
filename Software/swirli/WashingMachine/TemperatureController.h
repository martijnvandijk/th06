//
// Created by chiel on 20/01/16.
//

#ifndef PROJECT_TEMPERATURECONTROLLER_H
#define PROJECT_TEMPERATURECONTROLLER_H

#include "TemperatureRegulator.h"
#include "UARTUser.h"
#include "SensorListener.h"
#include "HeatingUnit.h"

/**
 * @brief controller used to monitor the temperature and keep it on a constant level
 */
class TemperatureController : public WashingMachine::UARTUser,
                              public TemperatureRegulator,
                              public WashingMachine::SensorListener {
public:
	TemperatureController(WashingMachine::HeatingUnit &heat);

	virtual void setTemperature(int heatLevel) override;

	virtual void update(int newVal) override;

	virtual int getTargetTemperature();
	virtual int getCurrentTemperature();

protected:
	virtual void main() override;

private:
	WashingMachine::HeatingUnit &heat;
	RTOS::pool<int> targetTemperature;

	RTOS::flag targetTemperatureUpdated;
	RTOS::pool<int> latestTemperature;
	RTOS::flag temperatureUpdated;
};


#endif //PROJECT_TEMPERATURECONTROLLER_H
