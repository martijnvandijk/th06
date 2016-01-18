cmake_minimum_required(VERSION 3.0)
project(swirli)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libs/googletest-master)
include_directories(${GTEST_INCLUDE_DIRS} libs)

set(WashingMachineSourceFiles
		WashingMachine/Door.cpp WashingMachine/Door.h
		WashingMachine/HeatingUnit.cpp WashingMachine/HeatingUnit.h
		WashingMachine/SignalLed.cpp WashingMachine/SignalLed.h
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
		WashingMachine/UARTHandler.cpp WashingMachine/UARTHandler.h
		WashingMachine/UARTUser.h)

set(RTOS_SourceFiles
	libs/pRTOS.cpp libs/pRTOS.h
	libs/libfiber.cpp libs/libfiber.h
	libs/libserial.cpp libs/libserial.h
)


set(MainSourceFiles
	main.cpp
)

add_executable(swirli ${WashingMachineSourceFiles} ${MainSourceFiles} ${RTOS_SourceFiles})
target_link_libraries(swirli pthread rt)

add_executable(swirli_testing test_main.cpp ${WashingMachineSourceFiles} ${RTOS_SourceFiles})
target_link_libraries(swirli_testing gtest pthread rt)

if (CMAKE_CROSSCOMPILING)
	add_custom_target(swirli_pi)
	add_custom_command(TARGET swirli_pi
			POST_BUILD
			COMMAND rsync
			ARGS -ahe ssh --timeout=10
			${PROJECT_SOURCE_DIR}/
			$<TARGET_FILE:swirli>
			$<TARGET_FILE:swirli_testing>
			pi@10.10.0.10:swirli_cmake
			WORKING_DIRECTORY .)
endif ()