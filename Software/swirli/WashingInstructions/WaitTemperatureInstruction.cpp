//
// Created by chiel on 24/01/16.
//

#include "WaitTemperatureInstruction.h"

WaitTemperatureInstruction::WaitTemperatureInstruction(TemperatureRegulator &regulator):
		regulator(regulator) {
}

void WaitTemperatureInstruction::execute(WashingMachine::UARTUser *user, LogController &logController) {
	regulator.wait(user);
}
