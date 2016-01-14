//
// Created by chiel on 13/01/16.
//

#include <gtest/gtest.h>
#include <iostream>
using namespace std;

TEST(Full, Printer) {
	ASSERT_TRUE(cout << "Testing" << endl);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	int test_result = RUN_ALL_TESTS();
	return test_result;
}