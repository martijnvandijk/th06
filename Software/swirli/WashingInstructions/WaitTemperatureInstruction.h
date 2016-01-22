//
// Created by chiel on 24/01/16.
//

#ifndef PROJECT_WAITTEMPERATUREINSTRUCTION_H
#define PROJECT_WAITTEMPERATUREINSTRUCTION_H

#include "../WashingInstruction.h"
#include "../TemperatureRegulator.h"

class WaitTemperatureInstruction : public WashingInstruction {
public:
	WaitTemperatureInstruction(TemperatureRegulator &regulator);

	virtual void execute(WashingMachine::UARTUser *user);

private:
	TemperatureRegulator &regulator;
};


#endif //PROJECT_WAITTEMPERATUREINSTRUCTION_H
