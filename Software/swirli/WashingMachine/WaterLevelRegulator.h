//
// Created by chiel on 18/01/16.
//

#ifndef WATERLEVELREGULATOR_H
#define WATERLEVELREGULATOR_H

#include "../EventGenerator.h"

class WaterLevelRegulator : public EventGenerator {
public:
	/**
	 * @brief Set the desired water level in the washing machine drum.
	 * 
	 * @param waterLevel Percentage. Values from 0 to 100 are correct.
	 */
	virtual void setWaterLevel(int waterLevel) = 0;
};

#endif //WATERLEVELREGULATOR_H
