//
// Created by martijn on 1/14/16.
//

#ifndef SWIRLI_UARTUSER_H
#define SWIRLI_UARTUSER_H

#include <string>
#include <stdint.h>
#include <pRTOS.h>

namespace WashingMachine {
    class UARTUser : public RTOS::task{
    public:
        UARTUser(unsigned int priority, const char *name = ""):
                RTOS::task{priority, name},
                replyPool{(std::string{"UU "} + name + " replyPool").c_str()}
        {}

        void receiveReply(uint8_t replyByte){
            replyPool.write(replyByte);
        };
        uint8_t getReplyPoolContents(){
            return replyPool.read();

        };

    protected:
        RTOS::pool<uint8_t> replyPool;
        virtual void main() = 0;
    };


}

#endif //SWIRLI_UARTUSER_H
