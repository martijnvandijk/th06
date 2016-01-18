//
// Created by chiel on 13/01/16.
//
#include "gtest/gtest.h"
#define TEST_FORK(Suite, Test, code) TEST(Suite, Test) {EXPECT_EXIT({\
    code\
	exit(0);\
}, testing::ExitedWithCode{0}, "");}
using namespace std;

#include "WashingMachine/UARTHandler.h"

//TEST(UARTHandler, Send) {
//	LibSerial libSerial{};
//	WashingMachine::UARTHandler handler{libSerial};
//	WashingMachine::UARTMessage message;
//	message.
//	handler.sendMessage();
//}

TEST(Full, Printer) {
	ASSERT_TRUE(cout << "Testing" << endl);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	int test_result = RUN_ALL_TESTS();
	return test_result;
}
