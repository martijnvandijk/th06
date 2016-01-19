//    class SignalLed{
    public:
        /**
         * @brief Constructor, specify UARTHandler
         *
         * @param uart The UARTHandler to be used for communicating with the emulator.
         */
        SignalLed(UARTHandler &uart);

        signalled_states_t getStatus(UARTUser *referenceUser);
        void setLed(signalled_states_t status, UARTUser *referenceUser);
        void toggleLed(UARTUser *referenceUser);

    private:
        UARTHandler &uart;
    }
// Created by martijn on 1/14/16.
//

#ifndef SWIRLI_UARTHANDLER_H
#define SWIRLI_UARTHANDLER_H

#include <stdint.h>
#include <pRTOS.h>
#include <libserial.h>
#include <queue>
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
        void main();
        RTOS::timer timer;
        std::queue<UARTMessage> OutputBuffer;
    };

}
#endif //SWIRLI_UARTHANDLER_H
