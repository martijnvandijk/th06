#ifndef SWIRLI_WASHINGTASK_H
#define SWIRLI_WASHINGTASK_H

#include <vector>
#include "WashingInstruction.h"
#include "../LogController.h"
#include "../WashingMachine/UARTUser.h"

// hier komt de taak die uitgevoed moet worden
// een taak bevat meerdere instructies

class WashingTask : public WashingInstruction {
public:
	void addInstruction(WashingInstruction *instruction); // has to be a pointer as the object will be stored in a array

	virtual void execute(WashingMachine::UARTUser *referenceUser, LogController &logController) override;

private:
	std::vector<WashingInstruction*> instructions{};
	friend class WashingProgram;
};

#endif