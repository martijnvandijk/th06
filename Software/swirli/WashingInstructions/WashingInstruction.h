#ifndef SWIRLI_WASHINGINSTRUCTION_H
#define SWIRLI_WASHINGINSTRUCTION_H

#include <string>
#include "../LogController.h"
#include "../WashingMachine/UARTUser.h"

/**
 * @brief Generalization of a washing instruction.
 * @details Used to execute steps of a washing program.
 * 
 * @param The UARTUser calling the function. Usually 'this' suffices.
 * @param logController The logging controller to log output to.
 * @param doWait Wether to wait for the instruction to finish.
 */
class WashingInstruction {
public:
	virtual void execute(
			WashingMachine::UARTUser *user,
			LogController &logController,
			bool doWait
	) = 0;
};

#endif