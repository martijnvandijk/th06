#ifndef WASHINGMACHINE_MOTOR_H
#define WASHINGMACHINE_MOTOR_H

#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
    class Motor{
    public:
        Motor(UARTHandler &uart);
        int getRPM();
        void setRPM(int rpm, UARTUser *referenceUser);
    private:
//        LibSerial &serialConnection;
    UARTHandler &uart;


//        virtual void receiveReply(uint8_t replyByte);
    };
}

#endif