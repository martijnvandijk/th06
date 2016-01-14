cmake_minimum_required(VERSION 3.0)
project(swirli)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(WashingMachineSourceFiles
        WashingMachine/Door.cpp WashingMachine/Door.h
        WashingMachine/HeatingUnit.cpp WashingMachine/HeatingUnit.h
        WashingMachine/LED.cpp WashingMachine/LED.h
        WashingMachine/Motor.cpp WashingMachine/Motor.h
        WashingMachine/Observable.cpp WashingMachine/Observable.h
        WashingMachine/Pump.cpp WashingMachine/Pump.h
        WashingMachine/SensorHandler.cpp WashingMachine/SensorHandler.h
        WashingMachine/SensorListener.h
        WashingMachine/SoapDispenser.cpp WashingMachine/SoapDispenser.h
        WashingMachine/TemperatureSensor.cpp WashingMachine/TemperatureSensor.h
        WashingMachine/WashingMachineBoundary.h
        WashingMachine/WaterLevelSensor.cpp WashingMachine/WaterLevelSensor.h
        WashingMachine/WaterValve.cpp WashingMachine/WaterValve.h
#        libs/Protocol.h
        )

set(RTOS_SourceFiles
        libs/pRTOS.cpp libs/pRTOS.h
        libs/libfiber.cpp libs/libfiber.h
        libs/libserial.cpp libs/libserial.h
        )

set(MainSourceFiles
        main.cpp
        )

add_executable(swirli ${SOURCE_FILES} ${WashingMachineSourceFiles} ${MainSourceFiles} ${RTOS_SourceFiles})