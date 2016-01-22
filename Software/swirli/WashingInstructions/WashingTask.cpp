#include "WashingTask.h"

void WashingTask::execute(WashingMachine::UARTUser *referenceUser, LogController &logController) {
	for (WashingInstruction *i : instructions) {
		i->execute(referenceUser, logController);
	}
}

void WashingTask::addInstruction(WashingInstruction *instruction) {
	instructions.push_back(instruction);
}
