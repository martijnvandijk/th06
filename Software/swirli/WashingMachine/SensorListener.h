#ifndef SWIRLI_SENSORLISTENER_H
#define SWIRLI_SENSORLISTENER_H
namespace WashingMachine{
	/**
	 * @brief Abstract class describing a sensor listener
	 * @details Used in a listener pattern
	 * 
	 */
    class SensorListener{
    public:
    	/**
    	 * @brief Push an update to the listener.
    	 * @details This method is called by the observable on polling.
    	 * 
    	 * @param newVal The new sensor value.
    	 */
        virtual void update(int newVal) = 0;
    };
}
#endif