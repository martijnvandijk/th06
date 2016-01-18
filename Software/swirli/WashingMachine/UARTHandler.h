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
    typedef struct{
        uint8_t requestByte;
        uint8_t commandByte;
        UARTUser *sender;
    } UARTMessage;

    class UARTHandler : public RTOS::task{
    public:
        UARTHandler(LibSerial &serial);
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

}
#endif //SWIRLI_UARTHANDLER_H
