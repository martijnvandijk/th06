//
// Created by chiel on 17/01/16.
//

#ifndef SETRPMINSTRUCTION_HPP
#define SETRPMINSTRUCTION_HPP

#include "../WashingMachine/Motor.h"
#include "WashingInstruction.h"
#include "../LogController.h"

class SetRPMInstruction : public WashingInstruction {
public:
	SetRPMInstruction(WashingMachine::Motor &motor, int rpm);

	virtual void execute(WashingMachine::UARTUser *user, LogController &logController, bool doWait) override;

private:
	WashingMachine::Motor &motor;
	int rpm;
};


#endif //SETRPMINSTRUCTION_HPP
