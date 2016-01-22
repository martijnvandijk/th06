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
                uart(uart),
                door{uart},
                heatingUnit{uart},
                motor{uart},
                pump{uart},
                signalLed{uart},
                soapDispenser{uart},
                temperatureSensor{uart},
                waterLevelSensor{uart},
                waterValve{uart} {
        }


        Door &getDoor()  {
            return door;
        }

        HeatingUnit &getHeatingUnit()  {
            return heatingUnit;
        }

        Motor &getMotor()  {
            return motor;
        }

        Pump &getPump(){
            return pump;
        }

        SignalLed &getSignalLed()  {
            return signalLed;
        }

        SoapDispenser &getSoapDispenser()  {
            return soapDispenser;
        }

        TemperatureSensor &getTemperatureSensor()  {
            return temperatureSensor;
        }

        WaterLevelSensor &getWaterLevelSensor()  {
            return waterLevelSensor;
        }

        WaterValve &getWaterValve() {
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
