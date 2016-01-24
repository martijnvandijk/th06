//
// Created by chiel on 18/01/16.
//

#ifndef SETWATERLEVELINSTRUCTION_H
#define SETWATERLEVELINSTRUCTION_H

#include "WashingInstruction.h"
#include "../WashingMachine/WaterLevelRegulator.h"
#include "../WashingMachine/UARTUser.h"

class SetWaterLevelInstruction : public WashingInstruction {
public:
	SetWaterLevelInstruction(WaterLevelRegulator &waterRegulator, int waterLevel);

	virtual void execute(
			WashingMachine::UARTUser *user,
			LogController &logController,
			bool doWait
	) override;

private:
	WaterLevelRegulator &waterRegulator;
	int waterLevel;
};


#endif //SETWATERLEVELINSTRUCTION_H
