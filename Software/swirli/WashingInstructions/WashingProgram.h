#ifndef SWIRLI_WASHINGPROGRAM_H
#define SWIRLI_WASHINGPROGRAM_H

#include <unordered_map>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>

#include "WashingTask.h"
#include "../WashingMachine/TemperatureRegulator.h"
#include "../WashingMachine/WaterLevelRegulator.h"
#include "../WashingMachine/WashingMachine.h"

class WashingProgram {
public:
	/**
	 * @brief Create a washing program out of a single main task
	 *
	 * @param mainTask the task to be executed
	 */
	WashingProgram(WashingTask *mainTask,
	               TemperatureRegulator &temperatureRegulator,
	               WaterLevelRegulator &waterLevelRegulator);
	/**
	 * @brief Create a washing program from a file
	 *
	 * @param filename the name of the file without the .json extension
	 * @param temperature the temperature that should be used when executing this program
	 * @param machine the hardware used for initialisation
	 */
	WashingProgram(std::string filename, int temperature,
	               WashingMachine::WashingMachine &machine,
	               TemperatureRegulator &temperatureRegulator,
	               WaterLevelRegulator &waterLevelRegulator);

	/**
	 * @brief start the washing program
	 *
	 * @param runner the task that runs and can stop this program
	 * @param logController the log to write to (for power failure safety)
	 */
	void execute(WashingProgramRunner &runner, LogController &logController);
	/**
	 * @see execute(WashingProgramRunner &runner, LogController &logController)
	 *
	 * @param resumeFrom the step to resume this program from, > 0 in case of a power failure/crash
	 */
	void execute(WashingProgramRunner &runner, LogController &logController, int resumeFrom);

	/**
	 * @brief write the program's info to a JSON writer, used for the web interface
	 */
	template<typename OutputStream>
	void writeJSONInfo(rapidjson::Writer<OutputStream> &writer) { // must be in the header due to compiler restrictions
		writer.Key(filename.c_str());
		{ writer.StartObject();
			writer.Key("temperature");
			{ writer.StartArray();
				for (int temperature : info.temperatures) {
					writer.Int(temperature);
				}
			} writer.EndArray();
			writer.Key("duration");
			writer.Int(info.duration);
			writer.Key("name");
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