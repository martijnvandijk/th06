//
// Created by chiel on 13/01/16.
//
#define debug_task_logging 1

#include <Protocol.h>
#include "gtest/gtest.h"
/* #define TEST_FORK(Suite, Test, code) TEST(Suite, Test) {EXPECT_EXIT({\
    code\
	exit(0);\
}, testing::ExitedWithCode{0}, "");}*/

using namespace std;

#include "WashingMachine/UARTHandler.h"
#include "WashingProgram.h"
#include "WashingMachine/Motor.h"
#include "WashingInstructions/SetRPMInstruction.h"
#include "WashingInstructions/WaitTimeInstruction.h"
#include "WashingInstructions/SetDoorLockInstruction.h"

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
		for (int i{0}; i < 16; i++) {
			program.execute(this, logController);
		}
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
//	WashingMachine::Door door{uartHandler};

	WashingProgram program{};
	WashingTask task{};
//	task.addInstruction(new SetDoorLockInstruction{door, true});
	task.addInstruction(new SetRPMInstruction{motor, 100});
	task.addInstruction(new WaitTimeInstruction{1 S});
	task.addInstruction(new SetRPMInstruction{motor, -100});
	task.addInstruction(new WaitTimeInstruction{1 S});
	task.addInstruction(new SetRPMInstruction{motor, 0});
	task.addInstruction(new WaitTimeInstruction{1 S});
//	task.addInstruction(new SetDoorLockInstruction{door, true});
//	task.addInstruction(new WaitTimeInstruction{1 S});
	program.addTask(task);

	LogController logController{};
	TestProgramUser test{program, logController};

	RTOS::display_statistics();
	ASSERT_EXIT({ RTOS::run(); }, testing::ExitedWithCode(1), "");
}

TEST(Full, Printer) {
	ASSERT_TRUE(cout << "Testing" << endl);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	int test_result = RUN_ALL_TESTS();
	return test_result;
}
