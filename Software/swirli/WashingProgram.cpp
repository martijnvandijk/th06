#include "WashingProgram.h"

void WashingProgram::addTask(WashingTask task) {
	tasks.push_back(task);
}

void WashingProgram::execute(WashingMachine::UARTUser *uartUser) {
	for (WashingTask &task : tasks) {
		task.execute(uartUser);
	}
}
