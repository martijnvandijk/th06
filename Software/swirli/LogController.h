#ifndef SWIRLI_LOGCONTROLLER_H
#define SWIRLI_LOGCONTROLLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class LogController {
public:
	/**
	 * do not use WashingProgram here because it creates a nasty circular dependency
	 * instead use a serialised string and don't care about the implementation
	 */
	LogController(std::ostream *log = new std::ofstream{"LogFile_WashingProgram"});
	
	/** \brief Write the program string to a file.
	*		Write a string to the LogFile_WashingProgram file (unless specified otherwise by the constructor).
	*
	*	@param program a string containing information about the started washing program.
	*/
	void logCurrentProgram(std::string program);
	
	/** \brief
	*
	*	@param
	*/
	void logCurrentName(std::string name);

	/** \brief Write an int to the logfile.
	*		Write an int to the ProgressFile_WashingProgram file. This int represents the current "step" in the washing program.
	*
	*	@param step an int representing the current step in the washing program.
	*/
	void logCurrentStep(int step);

	/** \brief Write a message to the file.
	*		Write a message explaining that the washing program has stopped.
	*
	*	@param
	*/
	void logProgramStopped();

	void logMessage(std::string source, std::string message);

private:
	std::ostream *log;
};

#endif