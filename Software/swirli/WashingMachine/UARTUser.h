//
// Created by martijn on 1/14/16.
//

#ifndef SWIRLI_UARTUSER_H
#define SWIRLI_UARTUSER_H

#include <string>
#include <stdint.h>
#include <pRTOS.h>

namespace WashingMachine {
    /**
     * @brief Generalization of a class that uses the UARTHandler.
     * 
     */
    class UARTUser : public RTOS::task{
    public:
        /**
         * @brief Constructor
         * @param priority The RTOS priority of this task.
         */
        UARTUser(unsigned int priority, const char *name = ""):
                RTOS::task{priority, name},
                replyPool{(std::string{"UU "} + name + " replyPool").c_str()}
        {}

        /**
         * @brief Receive a reply from a boundary object.
         * @details 
         * 
         * @param replyByte The byte sent back by the emulator.
         */
        virtual void receiveReply(uint8_t replyByte){
            replyPool.write(replyByte);
        };

        /**
         * @brief Get the reply pool contents.
         * @return The reply pool contents.
         */
        virtual uint8_t getReplyPoolContents(){
            return replyPool.read();

        };

    protected:
        RTOS::pool<uint8_t> replyPool;
        virtual void main() = 0;
    };


}

#endif //SWIRLI_UARTUSER_H
