cmake_minimum_required(VERSION 3.3)
project(pi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        pRTOS.cpp pRTOS.h
        libfiber.cpp libfiber.h
        libserial.cpp libserial.h
        )
add_executable(pi ${SOURCE_FILES})