#ifndef SWIRLI_WASHINGINSTRUCTION_H
#define SWIRLI_WASHINGINSTRUCTION_H

#include <string>
#include "../LogController.h"
#include "../WashingMachine/UARTUser.h"

class WashingInstruction {
public:
	virtual void execute(
			WashingMachine::UARTUser *user,
			LogController &logController,
			bool doWait
	) = 0;
};

#endif