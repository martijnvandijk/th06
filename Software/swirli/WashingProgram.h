#ifndef SWIRLI_WASHINGPROGRAM_H
#define SWIRLI_WASHINGPROGRAM_H

#include "WashingTask.h"
#include "LogController.h"

class WashingProgram {
public:
	void addTask(WashingTask task);

	void execute(WashingMachine::UARTUser *uartUser, LogController &logController);

	void execute(WashingMachine::UARTUser *uartUser, LogController &logController, int resumeFrom);

private:
	std::vector<WashingTask> tasks;
};

#endif