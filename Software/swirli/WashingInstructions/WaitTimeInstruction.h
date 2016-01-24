//
// Created by chiel on 19/01/16.
//

#ifndef PROJECT_WAITTIMEINSTRUCTION_H
#define PROJECT_WAITTIMEINSTRUCTION_H

#include "WashingInstruction.h"
#include "../WashingMachine/UARTUser.h"

class WaitTimeInstruction : public WashingInstruction {
public:
	WaitTimeInstruction(unsigned int time);

	virtual void execute(
			WashingMachine::UARTUser *user,
			LogController &logController,
			bool doWait
	) override;

private:
	unsigned int time;
};


#endif //PROJECT_WAITTIMEINSTRUCTION_H
