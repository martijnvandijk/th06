//
// Created by chiel on 24/01/16.
//

#ifndef PROJECT_WAITTEMPERATUREINSTRUCTION_H
#define PROJECT_WAITTEMPERATUREINSTRUCTION_H

#include "WashingInstruction.h"
#include "../WashingMachine/TemperatureRegulator.h"
#include "../WashingMachine/UARTUser.h"

class WaitTemperatureInstruction : public WashingInstruction {
public:
	WaitTemperatureInstruction(TemperatureRegulator &regulator);

	virtual void execute(WashingProgramRunner &runner,
	                     LogController &logController,
	                     bool doWait) override;

private:
	TemperatureRegulator &regulator;
};


#endif //PROJECT_WAITTEMPERATUREINSTRUCTION_H
