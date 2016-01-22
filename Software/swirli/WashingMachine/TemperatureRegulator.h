//
// Created by chiel on 18/01/16.
//

#ifndef TEMPERATUREREGULATOR_H
#define TEMPERATUREREGULATOR_H

#include "../EventGenerator.h"

class TemperatureRegulator : public EventGenerator {
public:
	virtual void setTemperature(int temperature) = 0;
};

#endif //TEMPERATUREREGULATOR_H
