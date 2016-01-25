#ifndef SWIRLI_WASHINGTASK_H
#define SWIRLI_WASHINGTASK_H

#include <vector>
#include <memory>
#include "WashingInstruction.h"
#include "../LogController.h"
#include "../WashingMachine/UARTUser.h"

class WashingTask : public WashingInstruction {
public:
	/**
	 * @brief add an instruction to this task
	 *
	 * @param instruction the instruction to be added
	 */
	void addInstruction(WashingInstruction *instruction); // has to be a pointer as the object will be stored in a array
	/**
	 * @brief shared pointer version of addInstruction
	 * @see addInstruction(WashingInstruction *instruction)
	 */
	void addInstruction(std::shared_ptr<WashingInstruction> &instruction);

	/**
	 * @brief execute this task and all it's instructions or sub-tasks
	 *
	 * @param runner The UARTUser calling the function. Usually 'this' suffices.
     * @param logController The logging controller to log output to.
     * @param doWait Whether to wait for the instruction to finish.
	 */
	virtual void execute(WashingProgramRunner &runner, LogController &logController, bool doWait) override;

private:
	std::vector<std::shared_ptr<WashingInstruction>> instructions;
	friend class WashingProgram;
};

#endif