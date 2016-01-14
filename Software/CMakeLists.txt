cmake_minimum_required(VERSION 3.0)

IF (CMAKE_BUILD_TYPE MATCHES "Release")
	set(target tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64)
	set(include_target ${CMAKE_CURRENT_LIST_DIR}/pi/cross/${target}/CMakeLists.txt)
	include(${include_target})
ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")

add_subdirectory(swirli)