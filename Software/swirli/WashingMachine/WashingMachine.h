//
// Created by martijn on 1/20/16.
//

#ifndef SWIRLI_WASHINGMACHINE_H
#define SWIRLI_WASHINGMACHINE_H

#include "Door.h"
#include "HeatingUnit.h"
#include "Motor.h"
#include "Pump.h"
#include "SignalLed.h"
#include "SoapDispenser.h"
#include "TemperatureSensor.h"
#include "WaterLevelSensor.h"
#include "WaterValve.h"

namespace WashingMachine {
    class WashingMachine {
    public:
        WashingMachine(
                UARTHandler &uart
        ) :
                uart{uart},
                door(uart),
                heatingUnit(uart),
                motor(uart),
                pump(uart),
                signalLed(uart),
                soapDispenser(uart),
                temperatureSensor(uart),
                waterLevelSensor(uart),
                waterValve(uart)
        {
            }


        Door &getDoor() const {
            return door;
        }

        HeatingUnit &getHeatingUnit() const {
            return heatingUnit;
        }

        Motor &getMotor() const {
            return motor;
        }

        Pump &getPump() const {
            return pump;
        }

        SignalLed &getSignalLed() const {
            return signalLed;
        }

        SoapDispenser &getSoapDispenser() const {
            return soapDispenser;
        }

        TemperatureSensor &getTemperatureSensor() const {
            return temperatureSensor;
        }

        WaterLevelSensor &getWaterLevelSensor() const {
            return waterLevelSensor;
        }

        WaterValve &getWaterValve() const {
            return waterValve;
        }

    private:
        UARTHandler &uart;
        Door door;
        HeatingUnit heatingUnit;
        Motor motor;
        Pump pump;
        SignalLed signalLed;
        SoapDispenser soapDispenser;
        TemperatureSensor temperatureSensor;
        WaterLevelSensor waterLevelSensor;
        WaterValve waterValve;
    };
}


#endif //SWIRLI_WASHINGMACHINE_H
