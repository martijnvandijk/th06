#include "LogController.h"
#include <iostream>
#include <fstream>
#include <ctime>

LogController(string nm) : logname{nm} {}

void LogController::logCurrentProgram(std::string program) {
	std::cout << "Started program: " << program << std::endl;
	
	time_t now = time(0); // Get current time
	char *dt = ctime(&now); // Convert to a readable string form
	
	ofstream log(logname, std::ios::app); // Open a file with the append parameter
	log.open();
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	log << "----Washing program [" << program << "] STARTED at " << dt << "----" << std::endl;
	
	log.close();
}

void LogController::logCurrentStep(int step) {
	std::cout << "Starting step " << step << " in program" << std::endl;
	
	ofstream log;
	progresslog.open("ProgressFile_WashingProgram"); // Create a file with the date and time in the name
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	log << step << std::endl;
	
	log.close();
}

void LogController::logProgramStopped() {
	std::cout << "Washing ended" << std::endl << std::endl;
	
	time_t now = time(0); // Get current time
	char *dt = ctime(&now); // Convert to a readable string form
	
	ofstream log(logname, std::ios::app); // Create a file with the append parameter
	log.open();
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	log << "----Washing program [" << program << "] ENDED at " << dt << "----" << std::endl << std::endl;
	
	log.close();
}
