//
// Created by chiel on 18/01/16.
//

#ifndef SETTEMPERATUREINSTRUCTION_H
#define SETTEMPERATUREINSTRUCTION_H

#include "../WashingInstruction.h"
#include "../TemperatureRegulator.h"

class SetTemperatureInstruction: WashingInstruction {
public:
	SetTemperatureInstruction(TemperatureRegulator &temperatureRegulator, int temperature);

	virtual void execute(WashingMachine::UARTUser *user) override;

private:
	TemperatureRegulator &temperatureRegulator;
	int temperature;
};


#endif //SETTEMPERATUREINSTRUCTION_H
