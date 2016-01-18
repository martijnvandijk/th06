//
// Created by chiel on 18/01/16.
//

#ifndef SETWATERLEVELINSTRUCTION_H
#define SETWATERLEVELINSTRUCTION_H

#include "../WashingInstruction.h"
#include "../WaterLevelRegulator.h"

class SetWaterLevelInstruction: public WashingInstruction {
public:
	SetWaterLevelInstruction(WaterLevelRegulator &waterRegulator, int waterLevel);

	virtual void execute(WashingMachine::UARTUser *user) override;

private:
	WaterLevelRegulator &waterRegulator;
	int waterLevel;
};


#endif //SETWATERLEVELINSTRUCTION_H
