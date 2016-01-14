//
// Created by martijn on 1/13/16.
//

#include "SensorListener.h"
#include "Observable.h"

void WashingMachine::Observable::subscribe(::WashingMachine::SensorListener* listener) {
    listeners.push_back(listener);
}
