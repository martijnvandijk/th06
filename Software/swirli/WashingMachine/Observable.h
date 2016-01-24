#ifndef WASHINGMACHINE_OBSERVABLE_H
#define WASHINGMACHINE_OBSERVABLE_H
#include <vector>
#include "SensorListener.h"
#include "UARTUser.h"
#include "UARTHandler.h"

namespace WashingMachine{
	/**
	 * @brief Generalization of an observable class.
	 * @details Used for implementing a listener pattern.
	 * 
	 */
    class Observable{
    public:
    	/**
    	 * @brief Subscribe to the observable
    	 * 
    	 * @param listener The listener to send updates to.
    	 */
        void subscribe(SensorListener* listener);
        virtual int poll(UARTUser *referenceUser) = 0;

    protected:
        void updateAll(int newVal);

    private:
        std::vector<SensorListener*> listeners;
    };
}
#endif