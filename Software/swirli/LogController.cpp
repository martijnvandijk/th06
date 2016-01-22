#include <bitset>
#include "LogController.h"

struct washingProgramState {
	std::string naam;
	int step;
};

LogController::LogController(std::ostream *log) : log{log} {}

void LogController::logCurrentProgram(std::string program) {
	time_t now = time(0); // Get current time
	char *dt = ctime(&now); // Convert to a readable string form
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	*log << "----Washing program [" << program << "] STARTED at " << dt << "----" << std::endl;
}

void LogController::logCurrentName(std::string name) {
	std::ofstream namelog{"NameFile_WashingProgram"};
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	namelog << name;
	
	namelog.close();
}

void LogController::logCurrentStep(int step) {
	*log << "----Starting step " << step << " in program----" << std::endl;
	
	std::ofstream progresslog{"ProgressFile_WashingProgram"};
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	progresslog << std::bitset<8>(step);
	
	progresslog.close();
}

void LogController::logProgramStopped() {	
	time_t now = time(0); // Get current time
	char *dt = ctime(&now); // Convert to a readable string form
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	*log << "----Washing program ENDED at " << dt << "----" << std::endl << std::endl;
}
