cmake_minimum_required(VERSION 3.0)
project(pi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        libs/pRTOS.cpp libs/pRTOS.h
        libs/libfiber.cpp libs/libfiber.h
        libs/libserial.cpp libs/libserial.h
        )
add_executable(swirli ${SOURCE_FILES})