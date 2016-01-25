//
// Created by chiel on 18/01/16.
//

#include "SetTemperatureInstruction.h"

SetTemperatureInstruction::SetTemperatureInstruction(
		TemperatureRegulator &temperatureRegulator,
		int temperature
) :
		temperatureRegulator(temperatureRegulator),
		temperature{temperature} { }

void SetTemperatureInstruction::execute(WashingProgramRunner &runner,
                                        LogController &logController,
                                        bool doWait) {
	std::cout << "setting temperature: " << temperature << std::endl;
	temperatureRegulator.setTemperature(temperature);
}
