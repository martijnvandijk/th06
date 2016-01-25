//
// Created by chiel on 21/01/16.
//

#ifndef PROJECT_EVENTGENERATOR_H
#define PROJECT_EVENTGENERATOR_H

#include <queue>
#include <pRTOS.h>

class EventGenerator {
public:
	EventGenerator(RTOS::task *parent);

	/**
	 * @return an RTOS::waitable that gets notified when this object generates an event
	 */
	RTOS::waitable waitEvent();

protected:
	bool notify();
	void notifyAll();

private:
	RTOS::pool<int> waiting;
	RTOS::flag flag;
};


#endif //PROJECT_EVENTGENERATOR_H
