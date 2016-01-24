//
// Created by chiel on 19/01/16.
//

#include "WaitTimeInstruction.h"

WaitTimeInstruction::WaitTimeInstruction(unsigned int time):
		time{time}
{}

void WaitTimeInstruction::execute(WashingMachine::UARTUser *user, LogController &logController, bool doWait) {
	std::cout << "user " << user << ", doWait " << doWait << ", time " << time << std::endl;
	if (doWait) {
		user->sleep(time);
	}
}
