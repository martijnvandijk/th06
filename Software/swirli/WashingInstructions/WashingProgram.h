#ifndef SWIRLI_WASHINGPROGRAM_H
#define SWIRLI_WASHINGPROGRAM_H

#include <unordered_map>
#include <memory>
#include "WashingTask.h"

class WashingProgram {
public:
	WashingProgram(WashingTask *mainTask);
	WashingProgram(std::string filename);

	void execute(WashingMachine::UARTUser *uartUser, LogController &logController);
	void execute(WashingMachine::UARTUser *uartUser, LogController &logController, int resumeFrom);

	std::string getJsonInfoString();

private:
	struct info {
		int temperatures[];
		int duration;
		std::string fullName;
	};

	std::shared_ptr<WashingTask> mainTask;
};

#endif