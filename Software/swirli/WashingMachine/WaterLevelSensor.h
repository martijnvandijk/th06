#ifndef WATERMACHINE_WATERLEVELSENSOR_H
#define WATERMACHINE_WATERLEVELSENSOR_H
#include "Observable.h"
#include "WashingMachineBoundary.h"

namespace WashingMachine{
    class WaterLevelSensor : public Observable {
    public:
        WaterLevelSensor(UARTHandler &uart);
        int poll(UARTUser *referenceUser);
    private:
    	UARTHandler &uart;

    };
}

#endif