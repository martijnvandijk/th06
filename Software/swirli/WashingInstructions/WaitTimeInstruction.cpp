//
// Created by chiel on 19/01/16.
//

#include "WaitTimeInstruction.h"

WaitTimeInstruction::WaitTimeInstruction(unsigned int time) :
		time{time} { }

void WaitTimeInstruction::execute(WashingProgramRunner &runner,
                                  LogController &logController,
                                  bool doWait) {
	if (doWait) {
		std::cout << "waiting " << time << " µs" << std::endl;
//		runner.sleep(time);
		runner.sleepTimer.set(time);
		RTOS::event event{runner.wait(runner.sleepTimer + runner.waitStopped())};
		if (!(event == runner.sleepTimer)) {
			runner.sleepTimer.cancel();
		}
	}
}
