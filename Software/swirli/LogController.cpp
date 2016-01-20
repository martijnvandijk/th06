#include "LogController.h"

void LogController::logCurrentProgram(std::string program) {
	std::cout << "Started program: " << program << std::endl;
}

void LogController::logCurrentStep(int step) {
	std::cout << "Starting step " << step << " in program" << std::endl;
}

void LogController::logProgramStopped() {
	std::cout << "Washing ended" << std::endl << std::endl;
}
