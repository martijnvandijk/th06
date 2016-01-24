//
// Created by chiel on 18/01/16.
//

#ifndef SETTEMPERATUREINSTRUCTION_H
#define SETTEMPERATUREINSTRUCTION_H


#include "WashingInstruction.h"
#include "../WashingMachine/TemperatureRegulator.h"
#include "../WashingMachine/UARTUser.h"

class SetTemperatureInstruction : public WashingInstruction {
public:
	SetTemperatureInstruction(TemperatureRegulator &temperatureRegulator, int temperature);

	virtual void execute(
			WashingMachine::UARTUser *user,
			LogController &logController,
			bool doWait
	) override;

private:
	TemperatureRegulator &temperatureRegulator;
	int temperature;
};


#endif //SETTEMPERATUREINSTRUCTION_H
