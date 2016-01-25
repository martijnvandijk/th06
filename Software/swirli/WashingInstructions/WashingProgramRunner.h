//
// Created by chiel on 24/01/16.
//

#ifndef PROJECT_WASHINGPROGRAMRUNNER_H
#define PROJECT_WASHINGPROGRAMRUNNER_H

#include <pRTOS.h>
#include "../WashingMachine/UARTUser.h"

class WashingProgramRunner : public WashingMachine::UARTUser {
public:
	WashingProgramRunner(unsigned int priority, const char *name = "");

	/**
	 * tells whether the current program is stopped (or should stop)
	 */
	bool isStopped();
	/**
	 * returns an RTOS::waitable that triggers when the program gets stopped
	 */
	RTOS::waitable waitStopped();
	/**
	 * stop the running program
	 */
	void stop();

	RTOS::timer sleepTimer;

protected:
	RTOS::pool<bool> stopped;
	RTOS::flag stoppedEvent;
};

#endif //PROJECT_WASHINGPROGRAMRUNNER_H
