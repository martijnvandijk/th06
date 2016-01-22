//
// Created by chiel on 13/01/16.
//
#define debug_task_logging 1

#include <Protocol.h>
#include "gtest/gtest.h"

using namespace std;

#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/Motor.h"
#include "WashingInstructions/SetRPMInstruction.h"
#include "WashingInstructions/WaitTimeInstruction.h"
#include "WashingInstructions/SetDoorLockInstruction.h"
#include "WashingInstructions/SetWaterLevelInstruction.h"
#include "WashingMachine/SensorHandler.h"
#include "WashingMachine/WaterLevelSensor.h"
#include "WashingInstructions/SetTemperatureInstruction.h"
#include "WashingMachine/TemperatureSensor.h"
#include "WashingInstructions/WaitWaterLevelInstruction.h"
#include "WashingInstructions/WaitTemperatureInstruction.h"
#include "WashingInstructions/WashingProgram.h"
#include "WashingMachine/WaterValve.h"
#include "WashingMachine/Pump.h"
#include "WashingMachine/HeatingUnit.h"
#include "WashingMachine/WaterLevelController.h"
#include "WashingMachine/TemperatureController.h"

TEST(WashingProgram, ReadFromFile) {
	WashingProgram program{"bonte_was"};

	std::cout << program.getJsonInfoString() << std::endl;
}

class TestProgramUser: public WashingMachine::UARTUser {
public:
	TestProgramUser(WashingProgram &program, LogController &logController):
			UARTUser{999, "TestProgramUser"},
	        program(program),
	        logController(logController)
	{}

protected:
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
	virtual void main() {
		program.execute(this, logController);
	}
#pragma clang diagnostic pop

private:
	WashingProgram &program;
	LogController &logController;
};

TEST(WashingProgram, Complete) {
	LibSerial libSerial{};
	libSerial.open("/dev/ttyAMA0", 9600);
	uint8_t commandStart[2];
	commandStart[0]=MACHINE_REQ;
	commandStart[1]=START_CMD;
	libSerial.write(commandStart,2);
	libSerial.flush();

	WashingMachine::UARTHandler uartHandler{libSerial};
	WashingMachine::Motor motor{uartHandler};
	WashingMachine::Door door{uartHandler};
	WashingMachine::Pump pump{uartHandler};
	WashingMachine::WaterValve waterValve{uartHandler};
	WashingMachine::HeatingUnit heatingUnit{uartHandler};

	SensorHandler handler{};
	WashingMachine::WaterLevelSensor waterLevelSensor{uartHandler};
	handler.addSensor(&waterLevelSensor);
	WaterLevelController waterLevelController{pump, waterValve};
	waterLevelSensor.subscribe(&waterLevelController);

	WashingMachine::TemperatureSensor temperatureSensor{uartHandler};
	handler.addSensor(&temperatureSensor);
	TemperatureController temperatureController{heatingUnit};
	temperatureSensor.subscribe(&temperatureController);

	WashingTask task{};
	task.addInstruction(new SetWaterLevelInstruction{waterLevelController, 20});
	task.addInstruction(new WaitWaterLevelInstruction{waterLevelController});
	task.addInstruction(new SetTemperatureInstruction{temperatureController, 30});
	task.addInstruction(new WaitTemperatureInstruction{temperatureController});

	task.addInstruction(new SetRPMInstruction{motor, 300});
	task.addInstruction(new WaitTimeInstruction{6 S});
	task.addInstruction(new SetRPMInstruction{motor, -300});
	task.addInstruction(new WaitTimeInstruction{6 S});
	task.addInstruction(new SetRPMInstruction{motor, 0});

	task.addInstruction(new SetWaterLevelInstruction{waterLevelController, 0});
	task.addInstruction(new SetTemperatureInstruction{temperatureController, 0});
	task.addInstruction(new WaitWaterLevelInstruction{waterLevelController});
	task.addInstruction(new WaitTimeInstruction{5 S});
	WashingProgram program{&task};

	LogController logController{&std::cout};
	TestProgramUser test{program, logController};

	RTOS::display_statistics();
	ASSERT_EXIT({ RTOS::run(); }, testing::ExitedWithCode(0), "");
}

TEST(Full, Printer) {
	ASSERT_TRUE(cout << "Testing" << endl);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	int test_result = RUN_ALL_TESTS();
	return test_result;
}
