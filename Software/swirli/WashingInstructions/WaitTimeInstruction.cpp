//
// Created by chiel on 19/01/16.
//

#include "WaitTimeInstruction.h"

WaitTimeInstruction::WaitTimeInstruction(unsigned int time) :
		time{time} { }

void WaitTimeInstruction::execute(WashingProgramRunner &runner,
                                  LogController &logController,
                                  bool doWait) {
	std::cout << "user " << runner << ", doWait " << doWait << ", time " << time << std::endl;
	if (doWait) {
		runner.sleep_timer->set(time);
		runner.wait(*runner.sleep_timer + runner.waitStopped());
	}
}
