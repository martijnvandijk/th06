//
// Created by martijn on 1/14/16.
//

#ifndef SWIRLI_UARTHANDLER_H
#define SWIRLI_UARTHANDLER_H

#include <stdint.h>
#include <pRTOS.h>
#include <libserial.h>
//#include <bits/stl_deque.h>
#include <deque>
#include "UARTUser.h"
namespace WashingMachine{

    class UARTHandler : public RTOS::task{
    public:
        /**
         * @brief Constructor, specify LibSerial connection
         * 
         * @param serial The LibSerial object to use 
         */
        UARTHandler(LibSerial &serial);

        /**
         * @brief Send a message to the emulator
         * 
         * @param m The UARTMessage to send
         */
        void sendMessage(UARTMessage m);
    private:
        LibSerial &serialConnection;
        RTOS::channel<UARTMessage, 64> InputBuffer;
        void handleUART();
        void main();
        int inputQueueCounter;
        RTOS::timer timer;
        std::deque<UARTMessage> OutputBuffer;
    };

    typedef struct{
        uint8_t requestByte;
        uint8_t commandByte;
        UARTUser *sender;
    } UARTMessage;
}
#endif //SWIRLI_UARTHANDLER_H
