#ifndef WASHINGMACHINE_MOTOR_H
#define WASHINGMACHINE_MOTOR_H

#include "../libs/libserial.h"

namespace WashingMachine{
    class Motor{
    public:
        Motor(LibSerial &serial);
        int getRPM();
        void setRPM(int rpm);
    private:
        LibSerial &serialConnection;

    };
}

#endif