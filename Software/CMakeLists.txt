cmake_minimum_required(VERSION 3.0)

message(STATUS "Build type is \"${CMAKE_BUILD_TYPE}\" \"$ENV{CMAKE_BUILD_TYPE}\"")

if ((NOT ($ENV{CMAKE_BUILD_TYPE} STREQUAL "Debug")) AND (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug")))
	message(STATUS "Building Release build")
	set(target tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64)
	set(include_target ${CMAKE_CURRENT_LIST_DIR}/pi/cross/${target}/CMakeLists.txt)
	include(${include_target})
endif ()

add_subdirectory(swirli)

message(STATUS "System arch is ${CMAKE_HOST_SYSTEM_PROCESSOR} -> ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Compiler: ${CMAKE_C_COMPILER} ${CMAKE_CXX_COMPILER}")