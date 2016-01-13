#ifndef WASHINGMACHINE_OBSERVABLE_H
#define WASHINGMACHINE_OBSERVABLE_H
#include <vector>

class Observable{
    Public:
        virtual void subscribe();
        virtual void poll();
};
#endif