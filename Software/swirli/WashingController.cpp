#include "WashingController.h"

WashingController::WashingController(LogController &logController,
                                     WashingMachine::UARTHandler &uartHandler,
                                     SensorHandler &sensorHandler,
                                     WashingMachine::WashingMachine &machine,
                                     TemperatureRegulator &temperatureRegulator,
                                     WaterLevelRegulator &waterLevelRegulator):
		WashingProgramRunner{0, "WashingController"},
		logController(logController),
		uartHandler(uartHandler),
		sensorHandler(sensorHandler),
		program{"WashControl program"},
		temperature{"WashControl temp"},
        programStarted{this, "Program started"},
        startTime{"WashControl startTime"},
        machine(machine),
        temperatureRegulator(temperatureRegulator),
        waterLevelRegulator(waterLevelRegulator)
{}

void WashingController::start(std::string programName, int programTemperature, int programDelay) {
	program.write(programName);
	temperature.write(programTemperature);

	programStarted.set();
}

long long int WashingController::timeStarted() {
	return startTime.read();
}

int WashingController::getTemperature() {
	return temperatureRegulator.getCurrentTemperature();
}

void WashingController::runProgram(WashingProgram &program, int step) {
	WashingMachine::UARTMessage message{MACHINE_REQ, START_CMD, this};
	uartHandler.sendMessage(message);

	machine.getDoor().waitClosed(this);
	// TODO DO NOT FORGET

	// start polling the sensors
	sensorHandler.resume();

	program.execute(*this, logController, step);

	endProgram();
}

void WashingController::endProgram() {
	stopped.write(false);

	resetMachineState();
}

void WashingController::resetMachineState() {
	machine.getMotor().setRPM(0, this);
	machine.getSoapDispenser().set(WashingMachine::SOAP_CLOSED, this);

	// turn off the heating
	temperatureRegulator.setTemperature(0);
	// pump away the water
	waterLevelRegulator.setWaterLevel(0);
	// wait for the water to be gone
	wait(waterLevelRegulator.waitEvent());

	// stop polling the sensors, machine can now idle
	sensorHandler.suspend();

	// reset all the hardware to the default state
	machine.getWaterValve().set(WashingMachine::VALVE_CLOSED, this);
	machine.getPump().set(WashingMachine::PUMP_OFF, this);
	machine.getHeatingUnit().set(WashingMachine::HEATINGUNIT_OFF, this);

	// finally unlock the door
	machine.getDoor().set(WashingMachine::DOOR_UNLOCKED_CLOSED, this);

	// stop the machine
	WashingMachine::UARTMessage message{MACHINE_REQ, STOP_CMD, this};
	uartHandler.sendMessage(message);
}

void WashingController::main() {
	std::cout << "starting WashingController" << std::endl;

	LogController::WashingProgramState unfinished = logController.getUnfinishedProgram();
	if (!unfinished.name.empty()) {
		// there was a program running, and the power failed
		WashingProgram readProgram{unfinished.name, unfinished.temperature,
		                           machine,
		                           temperatureRegulator,
		                           waterLevelRegulator};
		startTime.write(time(nullptr));
		runProgram(readProgram, unfinished.step);
	} else {
		WashingMachine::UARTMessage message{MACHINE_REQ, START_CMD, this};
		uartHandler.sendMessage(message);
		resetMachineState();
	}

	std::cout << "done initializing" << std::endl;
	for (;;) {
		RTOS::event event{wait(programStarted)};
		std::cout << "starting program " << program.read() << std::endl;

		sleep_timer->set(((unsigned long)(delay.read()) S) * 60);
		RTOS::event sleepEvent{wait(*sleep_timer + waitStopped())};
		if (sleepEvent == *sleep_timer) {
			try {
				WashingProgram readProgram{program.read(), temperature.read(),
				                           machine,
				                           temperatureRegulator,
				                           waterLevelRegulator};
				startTime.write(time(nullptr));
				runProgram(readProgram);
			} catch(std::invalid_argument &e){
				std::cerr << e.what() << std::endl;
			}
		} else {
			stopped.write(false);
		}

		// clear the started flag in case somebody tried to start washing while the machine was running
		programStarted.clear();
	}
}
