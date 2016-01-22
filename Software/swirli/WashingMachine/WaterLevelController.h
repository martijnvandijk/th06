//
// Created by chiel on 20/01/16.
//

#ifndef PROJECT_WATERLEVELCONTROLLER_H
#define PROJECT_WATERLEVELCONTROLLER_H

#include <pRTOS.h>
#include "WaterLevelRegulator.h"
#include "UARTUser.h"
#include "SensorListener.h"
#include "Pump.h"
#include "WaterValve.h"

class WaterLevelController : public WashingMachine::UARTUser, public WaterLevelRegulator, public WashingMachine::SensorListener {
public:
	WaterLevelController(WashingMachine::Pump &pump, WashingMachine::WaterValve &waterValve);

	virtual void setWaterLevel(int waterLevel) override;

	virtual void update(int newVal) override;

protected:
	virtual void main() override;

private:
	WashingMachine::Pump &pump;
	WashingMachine::WaterValve &waterValve;

	RTOS::pool<int> targetWaterLevel;
	RTOS::flag targetWaterLevelUpdated;

	RTOS::pool<int> latestWaterLevel;
	RTOS::flag waterLevelUpdated;
};


#endif //PROJECT_WATERLEVELCONTROLLER_H
