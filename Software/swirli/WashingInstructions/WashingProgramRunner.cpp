//
// Created by chiel on 24/01/16.
//

#include "WashingProgramRunner.h"

WashingProgramRunner::WashingProgramRunner(unsigned int priority, const char *name):
		UARTUser{priority, name},
		stopped{"Program stopped"},
		stoppedEvent{this, "Program stopped"},
		sleepTimer{this, "Runner sleepTimer"} {
	stopped.write(false);
}

bool WashingProgramRunner::isStopped() {
	return stopped.read();
}

RTOS::waitable WashingProgramRunner::waitStopped() {
	return stoppedEvent;
}

void WashingProgramRunner::stop() {
	stopped.write(true);
	stoppedEvent.set();
}
