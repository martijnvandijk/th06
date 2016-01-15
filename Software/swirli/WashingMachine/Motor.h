#ifndef WASHINGMACHINE_MOTOR_H
#define WASHINGMACHINE_MOTOR_H

#include "../libs/libserial.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
    class Motor{
    public:
        Motor(UARTHandler &uart);
        int getRPM(UARTUser *referenceUser);
        void setRPM(int rpm, UARTUser *referenceUser);
    private:
    UARTHandler &uart;

    };
}

#endif