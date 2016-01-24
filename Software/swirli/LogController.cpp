#include "LogController.h"

#define NAMEFILE_FILENAME "NameFile_WashingProgram"
#define STEPFILE_FILENAME "ProgressFile_WashingProgram"

LogController::LogController(std::ostream *log) : log{log} {}

void LogController::logProgramStarted(std::string filename, int temperature) {
	time_t now = time(0); // Get current time
	char *dt = ctime(&now); // Convert to a readable string form
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	*log << "----Washing program [" << (filename.empty() ? "local object" : filename) << "] STARTED at " << dt << "----" << std::endl;

	if (!filename.empty()) {
		// open the file for keeping track of the current program
		std::ofstream namelog{NAMEFILE_FILENAME};
		// Send information to the log file (parameters are set in brackets to more easily find them in the file
		namelog << filename << " " << temperature;
		namelog.close();
	}
}

void LogController::logCurrentStep(int step) {
	*log << "----Starting step " << step << " in program----" << std::endl;
	
	std::ofstream progresslog{STEPFILE_FILENAME, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary};
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	progresslog.write((char*)(&step), sizeof(char));
	
	progresslog.close();
}

void LogController::logProgramStopped() {
	time_t now = time(0); // Get current time
	char *dt = ctime(&now); // Convert to a readable string form
	
	// Send information to the log file (parameters are set in brackets to more easily find them in the file
	*log << "----Washing program ENDED at " << dt << "----" << std::endl << std::endl;

	// remove the temporary files for keeping track of the current program
	remove(NAMEFILE_FILENAME);
	remove(STEPFILE_FILENAME);
}

void LogController::logMessage(std::string source, std::string message) {
	*log << "[" << source << "] " << message << std::endl;
}

LogController::WashingProgramState LogController::getUnfinishedProgram() {
	WashingProgramState unfinished{"", 0, 0};
	std::ifstream nameFile{NAMEFILE_FILENAME};
	if (nameFile) {
		std::ifstream stepFile{STEPFILE_FILENAME};
		nameFile >> unfinished.name >> unfinished.temperature;
		stepFile >> unfinished.step;
	}
	return unfinished;
}
