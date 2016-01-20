#ifndef SWIRLI_LOGCONTROLLER_H
#define SWIRLI_LOGCONTROLLER_H

#include <string>
#include <iostream>

class LogController {
public:
	/**
	 * do not use WashingProgram here because it creates a nasty circular dependency
	 * instead use a serialised string and don't care about the implementation
	 */
	void logCurrentProgram(std::string program);

	void logCurrentStep(int step);

	void logProgramStopped();
};

#endif