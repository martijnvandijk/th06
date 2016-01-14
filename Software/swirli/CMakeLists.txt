cmake_minimum_required(VERSION 3.0)
project(pi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libs/googletest-master)
include_directories(${GTEST_INCLUDE_DIRS} libs)

set(SOURCE_FILES
        libs/pRTOS.cpp libs/pRTOS.h
        libs/libfiber.cpp libs/libfiber.h
        libs/libserial.cpp libs/libserial.h
        )
add_executable(swirli main.cpp ${SOURCE_FILES})
target_link_libraries(swirli pthread rt)

add_executable(swirli_testing test_main.cpp ${SOURCE_FILES})
target_link_libraries(swirli_testing gtest pthread rt)
