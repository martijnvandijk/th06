#include "WashingProgram.h"

void WashingProgram::addTask(WashingTask task) {
	tasks.push_back(task);
}

void WashingProgram::execute(WashingMachine::UARTUser *uartUser, LogController &logController) {
	execute(uartUser, logController, 0);
}

void WashingProgram::execute(WashingMachine::UARTUser *uartUser, LogController &logController, int resumeFrom) {
	logController.logCurrentProgram("this");
	for (int i{resumeFrom}; i < tasks.size(); i++) {
		logController.logCurrentStep(i);
		tasks[i].execute(uartUser);
	}
	// TODO put this in WashingController instead
	logController.logProgramStopped();
}
