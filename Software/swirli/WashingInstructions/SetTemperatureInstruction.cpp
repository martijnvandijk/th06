//
// Created by chiel on 18/01/16.
//

#include "SetTemperatureInstruction.h"

SetTemperatureInstruction::SetTemperatureInstruction(TemperatureRegulator &temperatureRegulator, int temperature):
		temperatureRegulator(temperatureRegulator),
        temperature{temperature}
{}

void SetTemperatureInstruction::execute(WashingMachine::UARTUser *user, LogController &logController, bool doWait) {
	temperatureRegulator.setTemperature(temperature);
}
