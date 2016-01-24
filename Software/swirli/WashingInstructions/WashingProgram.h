#ifndef SWIRLI_WASHINGPROGRAM_H
#define SWIRLI_WASHINGPROGRAM_H

#include <unordered_map>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
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
	WashingProgram(WashingTask *mainTask,
	               TemperatureRegulator &temperatureRegulator,
	               WaterLevelRegulator &waterLevelRegulator);
	WashingProgram(std::string filename, int temperature,
	               WashingMachine::WashingMachine &machine,
	               TemperatureRegulator &temperatureRegulator,
	               WaterLevelRegulator &waterLevelRegulator);

	void execute(WashingMachine::UARTUser *uartUser, LogController &logController);
	void execute(WashingMachine::UARTUser *uartUser, LogController &logController, int resumeFrom);

	template<typename OutputStream>
	void writeJSONInfo(rapidjson::Writer<OutputStream> &writer) { // must be in the header due to compiler restrictions
		writer.String(filename.c_str());
		{ writer.StartObject();
			writer.String("temperature");
			{ writer.StartArray();
				for (int temperature : info.temperatures) {
					writer.Int(temperature);
				}
			} writer.EndArray();
			writer.String("duration");
			writer.Int(info.duration);
			writer.String("name");
			writer.String(info.fullName.c_str());
		} writer.EndObject();
	}

private:
	std::string filename;
	int temperature;
	struct {
		std::vector<int> temperatures;
		int duration;
		std::string fullName;
	} info;

	std::shared_ptr<WashingTask> mainTask;

	// used for resuming washing programs
	TemperatureRegulator &temperatureRegulator;
	WaterLevelRegulator &waterLevelRegulator;
};

#endif