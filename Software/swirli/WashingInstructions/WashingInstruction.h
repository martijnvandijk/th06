#ifndef SWIRLI_WASHINGINSTRUCTION_H
#define SWIRLI_WASHINGINSTRUCTION_H

#include "../LogController.h"
#include "WashingProgramRunner.h"

class WashingInstruction {
public:
	/**
     * @brief Generalization of a washing instruction.
     * @details Used to execute steps of a washing program.
     *
     * @param The UARTUser calling the function. Usually 'this' suffices.
     * @param logController The logging controller to log output to.
     * @param doWait Whether to wait for the instruction to finish.
     */
	virtual void execute(WashingProgramRunner &runner, LogController &logController, bool doWait) = 0;
};

#endif