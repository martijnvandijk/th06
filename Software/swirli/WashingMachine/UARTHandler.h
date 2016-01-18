//
// Created by martijn on 1/14/16.
//

#ifndef SWIRLI_UARTHANDLER_H
#define SWIRLI_UARTHANDLER_H

#include <stdint.h>
#include <pRTOS.h>
#include <libserial.h>
#include <deque>
#include <bits/stl_queue.h>
#include "UARTUser.h"
namespace WashingMachine{
    typedef struct{
        uint8_t requestByte;
        uint8_t commandByte;
        UARTUser *sender;
    } UARTMessage;
    class UARTHandler : public RTOS::task{
    public:
    /**
     * @brief UART communications handler
     * @details provides a non-blocking way to communicate with the washing machine emulator.
     * 
     * @param serial A reference to the LibSerial instance used to communicated with the emulator.
     */
     UARTHandler(LibSerial &serial);
     void sendMessage(UARTMessage m);
 private:
    LibSerial &serialConnection;
    RTOS::channel<UARTMessage, 64> InputBuffer;
    RTOS::timer timer;
    std::deque<UARTMessage> OutputBuffer;
    void main();
};

}
#endif //SWIRLI_UARTHANDLER_H
