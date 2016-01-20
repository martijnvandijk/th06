//
// Created by chiel on 17/01/16.
//

#ifndef SETRPMINSTRUCTION_HPP
#define SETRPMINSTRUCTION_HPP

#include "../WashingInstruction.h"
#include "../WashingMachine/Motor.h"

class SetRPMInstruction : public WashingInstruction {
public:
	SetRPMInstruction(WashingMachine::Motor &motor, int rmp);

	virtual void execute(WashingMachine::UARTUser *user) override;

private:
	WashingMachine::Motor &motor;
	int rpm;
};


#endif //SETRPMINSTRUCTION_HPP
