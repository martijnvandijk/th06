#ifndef SWIRLI_WASHINGPROGRAM_H
#define SWIRLI_WASHINGPROGRAM_H

#include "WashingTask.h"

class WashingProgram {
public:
	void addTask(WashingTask task);

	void execute(WashingMachine::UARTUser *uartUser);

private:
	std::vector<WashingTask> tasks;
};

#endif