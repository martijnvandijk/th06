#ifndef WASHINGMACHINE_OBSERVABLE_H
#define WASHINGMACHINE_OBSERVABLE_H
#include <vector>
#include "SensorListener.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
    class Observable{
    public:
        void subscribe(SensorListener* listener);
        virtual int poll(UARTUser *referenceUser) = 0;

    private:
        std::vector<SensorListener*> listeners;
    };
}
#endif