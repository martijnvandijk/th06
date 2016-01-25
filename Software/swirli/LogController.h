#ifndef SWIRLI_LOGCONTROLLER_H
#define SWIRLI_LOGCONTROLLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
/**
 * @brief Controller for logging progress of running tasks.
 * 
 */
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
	void logProgramStarted(std::string filename, int temperature);

	/** \brief Write an int to the logfile.
	*		Write an int to the ProgressFile_WashingProgram file. This int represents the current "step" in the washing program.
	*
	*	@param step an int representing the current step in the washing program.
	*/
	void logCurrentStep(unsigned char step);

	/** \brief Write a message to the file.
	*		Write a message explaining that the washing program has stopped.
	*
	*	@param
	*/
	void logProgramStopped();

	/**
	 * @brief log a non-standard message to the log stream
	 *
	 * @param source the name of the thing that this message came from
	 * @param message the message
	 */
	void logMessage(std::string source, std::string message);

	typedef struct {
		std::string name;
		int temperature;
		int step;
	} WashingProgramState;
	WashingProgramState getUnfinishedProgram();

private:
	std::ostream *log;
};

#endif