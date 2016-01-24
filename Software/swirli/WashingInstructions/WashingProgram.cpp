#include "WashingProgram.h"

using namespace rapidjson;

WashingProgram::WashingProgram(WashingTask *mainTask, TemperatureRegulator &temperatureRegulator, WaterLevelRegulator &waterLevelRegulator) :
		mainTask{mainTask},
		filename{""},
		temperature{0},
		temperatureRegulator(temperatureRegulator),
		waterLevelRegulator(waterLevelRegulator) {
}

WashingProgram::WashingProgram(std::string filename,
                               int temperature,
                               WashingMachine::WashingMachine &machine,
                               TemperatureRegulator &temperatureRegulator,
                               WaterLevelRegulator &waterLevelRegulator):
		filename{filename},
		temperature{temperature},
		temperatureRegulator(temperatureRegulator),
		waterLevelRegulator(waterLevelRegulator) {
	std::unordered_map<std::string, std::shared_ptr<WashingTask>> tasks;

	Document document{};
	FILE * inFile{fopen(("WashingPrograms/" + filename + ".json").c_str(), "r")};
	char *readBuffer{new char[65536]};
	FileReadStream fileReadStream{inFile, readBuffer, 65536};
	document.ParseStream(fileReadStream);
	fclose(inFile);
	delete[] readBuffer;

	assert(document.HasMember("info"));
	assert(document["info"].HasMember("name"));
	assert(document["info"]["name"].IsString());
	assert(document["info"].HasMember("duration"));
	assert(document["info"]["duration"].IsNumber());
	assert(document["info"].HasMember("temperature"));
	assert(document["info"]["temperature"].IsArray());
	info.duration = document["info"]["duration"].GetInt();
	for (SizeType i; i < document["info"]["temperature"].Size(); i++) {
		assert(document["info"]["temperature"][i].IsNumber());
		info.temperatures.push_back(document["info"]["temperature"][i].GetInt());
	}
	info.fullName = document["info"]["name"].GetString();

	assert(document.HasMember("washing_tasks"));
	assert(document["washing_tasks"].IsObject());
	Value &tasksObject = document["washing_tasks"];
	for (Value::MemberIterator memI{tasksObject.MemberBegin()}; memI != tasksObject.MemberEnd(); ++memI) {
		//read the task to be made
		std::string taskName{memI->name.GetString()};
		WashingTask *task{new WashingTask{}};
		assert(memI->value.IsArray());
		Value &taskArray = memI->value;
		for (Value::ValueIterator itr{taskArray.Begin()}; itr != taskArray.End(); ++itr) {
			//read the instructions to be added
			std::shared_ptr<WashingInstruction> newInstruction{nullptr};
			if (itr->IsString()) {
				newInstruction = tasks[itr->GetString()];
			} else if (itr->IsArray()) {
				Value &instructionArray = *itr;
				assert(instructionArray[0].IsString());
				std::string instructionName{instructionArray[0].GetString()};
				if (instructionName == "add_soap") {
					newInstruction = std::shared_ptr<WashingInstruction>{new AddSoapInstruction{machine.getSoapDispenser()}};
				} else if (instructionName == "set_rpm") {
					int rpm;
					if (instructionArray[1].IsString()) {
						std::string paramName{instructionArray[1].GetString()};
						if (paramName == "-max") {
							rpm = -1600;
						} else if (paramName == "max") {
							rpm = 1600;
						} else {
							assert(false);
						}
					} else if (instructionArray[1].IsInt()) {
						rpm = instructionArray[1].GetInt();
					} else {
						assert(false);
					}
					newInstruction = std::shared_ptr<WashingInstruction>{new SetRPMInstruction{machine.getMotor(), rpm}};
				} else if (instructionName == "set_temp") {
					int temp;
					if (instructionArray[1].IsString()) {
						std::string paramName{instructionArray[1].GetString()};
						if (paramName == "temp") {
							temp = temperature;
						} else {
							assert(false);
						}
					} else if (instructionArray[1].IsInt()) {
						temp = instructionArray[1].GetInt();
					} else {
						assert(false);
					}
					newInstruction = std::shared_ptr<WashingInstruction>{new SetTemperatureInstruction{temperatureRegulator, temp}};
				} else if (instructionName == "set_water") {
					newInstruction = std::shared_ptr<WashingInstruction>{new SetWaterLevelInstruction{waterLevelRegulator, instructionArray[1].GetInt()}};
				} else if (instructionName == "wait_temp") {
					newInstruction = std::shared_ptr<WashingInstruction>{new WaitTemperatureInstruction{temperatureRegulator}};
				} else if (instructionName == "sleep") {
					newInstruction = std::shared_ptr<WashingInstruction>{new WaitTimeInstruction{instructionArray[1].GetUint() S}};
				} else if (instructionName == "wait_water") {
					newInstruction = std::shared_ptr<WashingInstruction>{new WaitWaterLevelInstruction{waterLevelRegulator}};
				} else {
					assert(false);
				}
			} else {
				assert(false);
			}

			if (newInstruction.get() != nullptr) {
				task->addInstruction(newInstruction);
			}
		}
		tasks[taskName] = std::shared_ptr<WashingTask>{task};
	}

	assert(document.HasMember("main_program"));
	assert(document["main_program"].IsString());
	mainTask = tasks[document["main_program"].GetString()];
}

void WashingProgram::execute(WashingMachine::UARTUser *uartUser, LogController &logController) {
	execute(uartUser, logController, 0);
}

void WashingProgram::execute(WashingMachine::UARTUser *uartUser, LogController &logController, int resumeFrom) {
	logController.logProgramStarted(filename, temperature);
	// adjust the temperature and the
	for (int i{0}; i < resumeFrom; ++i) {
		mainTask->instructions[i]->execute(uartUser, logController, false);
	}
	if (resumeFrom > 0) {
		WaitWaterLevelInstruction{waterLevelRegulator}.execute(uartUser, logController, true);
		if (temperatureRegulator.getTargetTemperature() > 20) {
			WaitTemperatureInstruction{temperatureRegulator}.execute(uartUser, logController, true);
		}
	}
	for (int i{resumeFrom}; i < mainTask->instructions.size(); i++) {
		logController.logCurrentStep(i);
		mainTask->instructions[i]->execute(uartUser, logController, true);
	}
	logController.logProgramStopped();
	// TODO put this in WashingController instead - or don't
}
