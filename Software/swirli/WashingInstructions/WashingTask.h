#ifndef SWIRLI_WASHINGTASK_H
#define SWIRLI_WASHINGTASK_H

#include <vector>
#include <memory>
#include "WashingInstruction.h"
#include "../LogController.h"
#include "../WashingMachine/UARTUser.h"

// hier komt de taak die uitgevoed moet worden
// een taak bevat meerdere instructies

class WashingTask : public WashingInstruction {
public:
	void addInstruction(WashingInstruction *instruction); // has to be a pointer as the object will be stored in a array
	void addInstruction(std::shared_ptr<WashingInstruction> &instruction);

	virtual void execute(WashingMachine::UARTUser *referenceUser, LogController &logController, bool doWait) override;

private:
	std::vector<std::shared_ptr<WashingInstruction>> instructions;
	friend class WashingProgram;
};

#endif