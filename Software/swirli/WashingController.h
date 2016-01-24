#ifndef SWIRLI_WASHINGCONTROLLER_H
#define SWIRLI_WASHINGCONTROLLER_H

#include "LogController.h"
#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/SensorHandler.h"
#include "WashingInstructions/WashingProgram.h"

class WashingController : public WashingMachine::UARTUser {
public:
	WashingController(LogController &logController,
	                  WashingMachine::UARTHandler &handler,
	                  SensorHandler &sensorHandler,
	                  WashingMachine::WashingMachine &machine,
	                  TemperatureRegulator &temperatureRegulator,
	                  WaterLevelRegulator &waterLevelRegulator);

	void start(std::string programName, int temperature, int programDelay);
	/**
	 * return the time when the washingProgram started, in seconds since the epoch
	 */
	long long int timeStarted();

protected:
	virtual void main() override;

private:
	/**
	 * run the program specified
	 * this includes things for the setup, like:
	 * - starting the sensors
	 * -
	 */
	void runProgram(WashingProgram &program, int step = 0);

	/**
	 * return the washing machine to the state ready for sleep.
	 * this includes doing things like:
	 * - pumping away water
	 * - disabling temperature control
	 * - stopping logging
	 * - other things
	 */
	void endProgram();

	/**
	 * reset to the default state of the machine
	 * will be called at every startup in case of a power failure, and after every WashingProgram
	 */
	void resetMachineState();

	RTOS::pool<std::string> program;
	RTOS::pool<int> temperature;
	RTOS::flag programStarted;
	RTOS::pool<long long int> startTime;

	LogController &logController;
	WashingMachine::UARTHandler &uartHandler;
	SensorHandler &sensorHandler;

	WashingMachine::WashingMachine &machine;
	TemperatureRegulator &temperatureRegulator;
	WaterLevelRegulator &waterLevelRegulator;
};

#endif