#ifndef WASHINGMACHINE_TEMPERATURESENSOR_H
#define WASHINGMACHINE_TEMPERATURESENSOR_H
#include "Observable.h"
#include "../libs/libserial.h"

namespace WashingMachine{
    class TemperatureSensor{
    public:
        /**
       * @brief Constructor, specify UARTHandler instance
       * 
       * @param uart The UARTHandler to be used for communicating with the emulator
       */
        TemperatureSensor(UARTHandler &uart);
        /**
         * @brief polls the temperature sensor
         * 
         * @param  referenceUser The UARTUser that is calling the function (usually 'this' suffices)
         * @return needs to be added
         */
        int poll(UARTUser *referenceUser);
    private:
    	UARTHandler &uart;

    };
}
#endif