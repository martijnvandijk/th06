//
// Created by chiel on 18/01/16.
//

#ifndef WATERLEVELREGULATOR_H
#define WATERLEVELREGULATOR_H

#include "../EventGenerator.h"

class WaterLevelRegulator : public EventGenerator {
public:
	virtual void setWaterLevel(int waterLevel) = 0;
};

#endif //WATERLEVELREGULATOR_H
