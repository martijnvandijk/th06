cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++11")


IF (CMAKE_BUILD_TYPE MATCHES "Release")
	set(target tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64)
	include(pi/cross/${target}/CMakeLists.txt)
ENDIF()

add_subdirectory(swirli)