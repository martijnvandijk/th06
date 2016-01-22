#ifndef SWIRLI_WASHINGPROGRAM_H
#define SWIRLI_WASHINGPROGRAM_H

#include <unordered_map>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include "AddSoapInstruction.h"
#include "SetRPMInstruction.h"
#include "SetTemperatureInstruction.h"
#include "SetWaterLevelInstruction.h"
#include "WaitTemperatureInstruction.h"
#include "WaitTimeInstruction.h"
#include "WaitWaterLevelInstruction.h"
#include "WashingTask.h"
#include "../WashingMachine/TemperatureRegulator.h"
#include "../WashingMachine/WashingMachine.h"
#include "../WashingMachine/WaterLevelRegulator.h"

class WashingProgram {
public:
	WashingProgram(WashingTask *mainTask);
	WashingProgram(std::string filename, int temperature,
	               WashingMachine::WashingMachine &machine,
	               TemperatureRegulator &temperatureRegulator,
	               WaterLevelRegulator &waterLevelRegulator);

	void execute(WashingMachine::UARTUser *uartUser, LogController &logController);
	void execute(WashingMachine::UARTUser *uartUser, LogController &logController, int resumeFrom);

	std::string getJsonInfoString();

private:
	std::string filename;
	struct {
		std::vector<int> temperatures;
		int duration;
		std::string fullName;
	} info;

	std::shared_ptr<WashingTask> mainTask;
};

#endif