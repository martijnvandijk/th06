#ifndef SWIRLI_SENSORLISTENER_H
#define SWIRLI_SENSORLISTENER_H
namespace WashingMachine{
    class SensorListener{
    public:
        virtual void update(int newVal) = 0;
    };
}
#endif