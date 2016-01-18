#ifndef SWIRLI_WASHINGTASK_H
#define SWIRLI_WASHINGTASK_H

#include <vector>
#include "WashingMachine/UARTUser.h"
#include "WashingInstruction.h"

// hier komt de taak die uitgevoed moet worden
// een taak bevat meerdere instructies

class WashingTask {
public:
	void addInstruction(WashingInstruction *instruction); // has to be a pointer as the object will be stored in a array

	void execute(WashingMachine::UARTUser *referenceUser);

private:
	std::vector<WashingInstruction*> instructions{};
};

#endif