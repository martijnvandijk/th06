//
// Created by martijn on 1/13/16.
//

#include "Observable.h"

void WashingMachine::Observable::subscribe(::WashingMachine::SensorListener* listener) {
    listeners.push_back(listener);
}

void WashingMachine::Observable::updateAll(int newVal) {
    for (SensorListener *listener : listeners) {
        listener->update(newVal);
    }
}
