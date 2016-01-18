#ifndef WASHINGMACHINE_TEMPERATURESENSOR_H
#define WASHINGMACHINE_TEMPERATURESENSOR_H
#include "Observable.h"
#include "../libs/libserial.h"

namespace WashingMachine{
    class TemperatureSensor{
    public:
        TemperatureSensor(UARTHandler &uart);
        int poll(UARTUser *referenceUser);
    private:
    	UARTHandler &uart;

    };
}
#endif