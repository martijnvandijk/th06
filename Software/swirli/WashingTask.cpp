#include "WashingTask.h"

void WashingTask::execute(WashingMachine::UARTUser *referenceUser) {
	for (WashingInstruction *i : instructions) {
		i->execute(referenceUser);
	}
}

void WashingTask::addInstruction(WashingInstruction *instruction) {
	instructions.push_back(instruction);
}
