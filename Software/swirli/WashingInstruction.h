#ifndef SWIRLI_WASHINGINSTRUCTION_H
#define SWIRLI_WASHINGINSTRUCTION_H

#include <string>
#include "WashingMachine/UARTUser.h"

class WashingInstruction {
public:
	virtual void execute(WashingMachine::UARTUser *user) = 0;
};

#endif