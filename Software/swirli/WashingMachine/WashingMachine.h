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
    /**
     * @brief Class for constructing boundary objects and accessing them.
     * 
     */
    class WashingMachine {
    public:
        /**
         * @brief Constructor.
         * 
         * @param uart The LibSerial instance to use to communicate to the hardware.
         */
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

        /**
         * @brief Get the washing machine door instance.
         * @return The washing machine door instance.
         */
        Door &getDoor()  {
            return door;
        }

        /**
         * @brief Get the washing machine heating unit instance.
         * @return The washing machine heating unit instance.
         */
        HeatingUnit &getHeatingUnit()  {
            return heatingUnit;
        }

        /**
         * @brief Get the washing machine motor instance.
         * @return The washing machine motor instance.
         */
        Motor &getMotor()  {
            return motor;
        }

        /**
         * @brief Get the washing machine pump instance.
         * @return The washing machine pump instance.
         */
        Pump &getPump(){
            return pump;
        }

        /**
         * @brief Get the washing machine signal led instance.
         * @details 
         * @return The washing machine signal led instance.
         */
        SignalLed &getSignalLed()  {
            return signalLed;
        }

        /**
         * @brief Get the washing machine soap dispenser instance.
         * @details 
         * @return The washing machine soap dispencer instance.
         */
        SoapDispenser &getSoapDispenser()  {
            return soapDispenser;
        }

        /**
         * @brief Get the washing machine temperature sensor.
         * @details 
         * @return The washing machine temperature sensor instance.
         */
        TemperatureSensor &getTemperatureSensor()  {
            return temperatureSensor;
        }

        /**
         * @brief Get the washing machine water level sensor instance.
         * @details 
         * @return The water level sensor instance.
         */
        WaterLevelSensor &getWaterLevelSensor()  {
            return waterLevelSensor;
        }

        /**
         * @brief Get the water level valve instance
         * @details 
         * @return The water level valve instance.
         */
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
