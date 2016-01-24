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
    /**
     * Used for sending messages to the UART interface.
     */
    typedef struct{
        uint8_t requestByte; ///< Used for selecting the washing machine part
        uint8_t commandByte; ///< Used for telling the washing machine part what to do.
        UARTUser *sender; ///< Pointer to the UARTUser who sent the command. Used for suspending and resuming that task.
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
