cmake_minimum_required(VERSION 3.0)
project(swirli)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O0")

add_subdirectory(libs/googletest-master)
include_directories(${GTEST_INCLUDE_DIRS} libs ${PI_INCLUDE_DIRS})

if (CMAKE_CROSSCOMPILING)
	set(SSL_LIBRARIES
			${PI_LINK_DIRS}/arm-linux-gnueabihf/libssl.so.1.0.0
			${PI_LINK_DIRS}/arm-linux-gnueabihf/libcrypto.so.1.0.0
			${PI_LINK_DIRS}/../../lib/arm-linux-gnueabihf/libz.so.1
			)

	add_definitions(-fdebug-prefix-map=${PROJECT_SOURCE_DIR}/=)
else()
	set(SSL_LIBRARIES ssl crypto)
endif ()


set(NetworkingSourceFiles
		libs/networking/base64.h libs/networking/base64.cpp
		libs/networking/broadcaster.h libs/networking/broadcaster.cpp
		libs/networking/PracticalSocket.h libs/networking/PracticalSocket.cpp
		libs/networking/websocket.h libs/networking/websocket.cpp
		)

set(WashingMachineSourceFiles
		WashingMachine/Door.cpp					WashingMachine/Door.h
		WashingMachine/HeatingUnit.cpp			WashingMachine/HeatingUnit.h
		WashingMachine/SignalLed.cpp			WashingMachine/SignalLed.h
		WashingMachine/Motor.cpp				WashingMachine/Motor.h
		WashingMachine/Observable.cpp			WashingMachine/Observable.h
		WashingMachine/Pump.cpp					WashingMachine/Pump.h
		WashingMachine/SensorHandler.cpp		WashingMachine/SensorHandler.h
		WashingMachine/SensorListener.h
		WashingMachine/SoapDispenser.cpp		WashingMachine/SoapDispenser.h
		WashingMachine/TemperatureSensor.cpp	WashingMachine/TemperatureSensor.h
		WashingMachine/WashingMachineBoundary.h
		WashingMachine/WaterLevelSensor.cpp		WashingMachine/WaterLevelSensor.h
		WashingMachine/WaterValve.cpp			WashingMachine/WaterValve.h
		WashingMachine/UARTHandler.cpp			WashingMachine/UARTHandler.h
		WashingMachine/UARTUser.h
		WashingInstruction.h
		WashingTask.cpp										WashingTask.h
		WashingProgram.cpp									WashingProgram.h
		WashingInstructions/SetRPMInstruction.cpp			WashingInstructions/SetRPMInstruction.h
		WashingInstructions/SetWaterLevelInstruction.cpp	WashingInstructions/SetWaterLevelInstruction.h
		WashingInstructions/SetTemperatureInstruction.cpp	WashingInstructions/SetTemperatureInstruction.h
		WashingInstructions/AddSoapInstruction.cpp			WashingInstructions/AddSoapInstruction.h
		WashingInstructions/SetDoorLockInstruction.cpp		WashingInstructions/SetDoorLockInstruction.h
		WashingInstructions/WaitTimeInstruction.cpp			WashingInstructions/WaitTimeInstruction.h
		TemperatureRegulator.h
		WaterLevelRegulator.h

		LogController.cpp						LogController.h TemperatureController.cpp TemperatureController.h WaterLevelController.cpp WaterLevelController.h WashingInstructions/WaitWaterLevelInstruction.cpp WashingInstructions/WaitWaterLevelInstruction.h EventGenerator.cpp EventGenerator.h WashingInstructions/WaitTemperatureInstruction.cpp WashingInstructions/WaitTemperatureInstruction.h)

set(RTOS_SourceFiles
	libs/pRTOS.cpp libs/pRTOS.h
	libs/libfiber.cpp libs/libfiber.h
	libs/libserial.cpp libs/libserial.h
)


set(MainSourceFiles
	main.cpp
)

add_executable(swirli
		${WashingMachineSourceFiles}
		${MainSourceFiles}
		${RTOS_SourceFiles}
		${NetworkingSourceFiles}
		)
target_link_libraries(swirli pthread rt ${SSL_LIBRARIES})

add_executable(swirli_testing
		test_main.cpp
		${WashingMachineSourceFiles}
		${RTOS_SourceFiles}
		)
target_link_libraries(swirli_testing gtest pthread rt ${SSL_LIBRARIES})

if (CMAKE_CROSSCOMPILING)
	add_custom_target(swirli_pi)
	add_custom_command(TARGET swirli_pi
			POST_BUILD
			COMMAND rsync
			ARGS -avhe ssh --timeout=10
			${PROJECT_SOURCE_DIR}/
			$<TARGET_FILE:swirli>
			$<TARGET_FILE:swirli_testing>
			pi@10.42.0.71:swirli_cmake
			WORKING_DIRECTORY .)
endif ()