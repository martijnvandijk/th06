//
// Created by chiel on 13/01/16.
//
#define debug_task_logging 1

#include <Protocol.h>
#include <rapidjson/writer.h>
#include "gtest/gtest.h"

using namespace std;

#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/WashingMachine.h"
#include "WashingMachine/SensorHandler.h"
#include "WashingMachine/WaterLevelController.h"
#include "WashingMachine/TemperatureController.h"
#include "WashingInstructions/SetRPMInstruction.h"
#include "WashingInstructions/SetWaterLevelInstruction.h"
#include "WashingInstructions/SetTemperatureInstruction.h"
#include "WashingInstructions/WaitWaterLevelInstruction.h"
#include "WashingInstructions/WaitTemperatureInstruction.h"
#include "WashingInstructions/WaitTimeInstruction.h"
#include "WashingInstructions/WashingProgram.h"

class TestProgramUser : public WashingMachine::UARTUser {
public:
	TestProgramUser(
			WashingProgram &program,
			LogController &logController,
			WashingMachine::UARTHandler &handler,
			SensorHandler &sensorHandler
	) :
			UARTUser{0, "TestProgramUser"},
			program(program),
			logController(logController),
			uartHandler(handler),
			sensorHandler(sensorHandler) { }

protected:
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

	virtual void main() {
		WashingMachine::UARTMessage message1{MACHINE_REQ, STATUS_CMD, this};
		uartHandler.sendMessage(message1);
		std::cout << "emulator status: " << std::hex << (int(getReplyPoolContents())) << std::endl;

		WashingMachine::UARTMessage message2{MACHINE_REQ, START_CMD, this};
		uartHandler.sendMessage(message2);
		std::cout << "emulator status: " << std::hex << (int(getReplyPoolContents())) << std::endl;

		// resume sensorhandler
		sensorHandler.resume();

		program.execute(this, logController);

		sensorHandler.suspend();
	}

#pragma clang diagnostic pop

private:
	WashingProgram &program;
	LogController &logController;
	WashingMachine::UARTHandler &uartHandler;
	SensorHandler &sensorHandler;
};

TEST(WashingProgram, ReadFromFile) {
	LibSerial libSerial{};
	libSerial.open("/dev/ttyAMA0", 9600);
//	uint8_t commandStart[2];
//	commandStart[0]=MACHINE_REQ;
//	commandStart[1]=START_CMD;
//	libSerial.write(commandStart,2);
//	libSerial.flush();

	WashingMachine::UARTHandler uartHandler{libSerial};
	WashingMachine::WashingMachine washingMachine{uartHandler};
	TemperatureController temperatureController{washingMachine.getHeatingUnit()};
	WaterLevelController waterLevelController{
			washingMachine.getPump(),
			washingMachine.getWaterValve()
	};

	SensorHandler handler{};
	handler.suspend();

	WashingMachine::WaterLevelSensor waterLevelSensor{uartHandler};
	handler.addSensor(&waterLevelSensor);
	waterLevelSensor.subscribe(&waterLevelController);

	WashingMachine::TemperatureSensor temperatureSensor{uartHandler};
	handler.addSensor(&temperatureSensor);
	temperatureSensor.subscribe(&temperatureController);

	WashingProgram program{
			"bonte_was",
			40,
			washingMachine,
			temperatureController,
			waterLevelController
	};

	LogController logController{&std::cout};
	TestProgramUser test{program, logController, uartHandler, handler};

	RTOS::display_statistics();
	ASSERT_EXIT({ RTOS::run(); }, testing::ExitedWithCode(0), "");

	rapidjson::StringBuffer stringBuffer{};
	rapidjson::Writer<rapidjson::StringBuffer> stringWriter{stringBuffer};
	program.writeJSONInfo(stringWriter);
	std::cout << stringBuffer.GetString() << std::endl;
}

TEST(WashingProgram, Complete) {
	LibSerial libSerial{};
	libSerial.open("/dev/ttyAMA0", 9600);
//	uint8_t commandStart[2];
//	commandStart[0]=MACHINE_REQ;
//	commandStart[1]=START_CMD;
//	libSerial.write(commandStart,2);
//	libSerial.flush();

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

	WashingTask *task{new WashingTask{}};
	task->addInstruction(new SetWaterLevelInstruction{waterLevelController, 20});
	task->addInstruction(new WaitWaterLevelInstruction{waterLevelController});
	task->addInstruction(new SetTemperatureInstruction{temperatureController, 30});
	task->addInstruction(new WaitTemperatureInstruction{temperatureController});

	task->addInstruction(new SetRPMInstruction{motor, 300});
	task->addInstruction(new WaitTimeInstruction{6 S});
	task->addInstruction(new SetRPMInstruction{motor, -300});
	task->addInstruction(new WaitTimeInstruction{6 S});
	task->addInstruction(new SetRPMInstruction{motor, 0});

	task->addInstruction(new SetWaterLevelInstruction{waterLevelController, 0});
	task->addInstruction(new SetTemperatureInstruction{temperatureController, 0});
	task->addInstruction(new WaitWaterLevelInstruction{waterLevelController});
	task->addInstruction(new WaitTimeInstruction{5 S});
	WashingProgram program{task, temperatureController, waterLevelController};

	LogController logCurrentName{&std::cout};
	LogController logController{&std::cout};
	TestProgramUser test{program, logController, uartHandler, handler};

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
