#include "WashingTask.h"

void WashingTask::execute(WashingMachine::UARTUser *referenceUser, LogController &logController) {
	for (std::shared_ptr<WashingInstruction> i : instructions) {
		std::cout << "Executing from " << this << ": " << i << " (a " << typeid(i).name() << ")" << std::endl;
		i->execute(referenceUser, logController);
	}
}

void WashingTask::addInstruction(WashingInstruction *instruction) {
	std::shared_ptr<WashingInstruction> ptr{instruction};
	addInstruction(ptr);
}

void WashingTask::addInstruction(std::shared_ptr<WashingInstruction> &instruction) {
	instructions.push_back(instruction);
}
