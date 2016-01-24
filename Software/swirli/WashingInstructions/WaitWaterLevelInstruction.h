//
// Created by chiel on 21/01/16.
//

#ifndef PROJECT_WAITWATERLEVEL_H
#define PROJECT_WAITWATERLEVEL_H

#include "WashingInstruction.h"
#include "../WashingMachine/WaterLevelRegulator.h"
#include "../WashingMachine/UARTUser.h"

class WaitWaterLevelInstruction : public WashingInstruction {
public:
	WaitWaterLevelInstruction(WaterLevelRegulator &water);

	virtual void execute(
			WashingMachine::UARTUser *user,
			LogController &logController,
			bool doWait
	) override;

private:
	WaterLevelRegulator &water;
};


#endif //PROJECT_WAITWATERLEVEL_H
