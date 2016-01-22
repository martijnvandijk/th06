#include <rapidjson/document.h>
#include "WashingProgram.h"

WashingProgram::WashingProgram(WashingTask *mainTask) : mainTask{mainTask} {
}

WashingProgram::WashingProgram(std::string filename) {
//	std::unordered_map<std::string, WashingTask> tasks;
//
//	std::ifstream inFile{filename};
//	rapidjson::Document document{};
//	document.ParseStream(inFile);
//	inFile.close();
//
//	assert(document.HasMember("washing_tasks"));
//	assert(document["washing_tasks"].IsObject());
//	for (rapidjson::Value &v : document["washing_tasks"]) {
//
//	}
}

std::string WashingProgram::getJsonInfoString() {
	return "{}"; // TODO
}

void WashingProgram::execute(WashingMachine::UARTUser *uartUser, LogController &logController) {
	execute(uartUser, logController, 0);
}

void WashingProgram::execute(WashingMachine::UARTUser *uartUser, LogController &logController, int resumeFrom) {
	logController.logCurrentProgram("this");
	for (int i{resumeFrom}; i < mainTask->instructions.size(); i++) {
		logController.logCurrentStep(i);
		mainTask->instructions[i]->execute(uartUser, logController);
	}
	logController.logProgramStopped();
	// TODO put this in WashingController instead - or don't
}
