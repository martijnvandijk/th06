#ifndef WASHINGMACHINE_OBSERVABLE_H
#define WASHINGMACHINE_OBSERVABLE_H
#include <vector>
#include "SensorListener.h"

namespace WashingMachine{
    class Observable{
    public:
        void subscribe(SensorListener* listener);
        virtual void poll() = 0;

    private:
        std::vector<SensorListener*> listeners;
    };
}
#endif