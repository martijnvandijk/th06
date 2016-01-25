//
// Created by chiel on 21/01/16.
//

#ifndef PROJECT_EVENTGENERATOR_H
#define PROJECT_EVENTGENERATOR_H

#include <queue>
#include <pRTOS.h>

class EventGenerator {
public:
	void waitEvent(RTOS::task *user);

protected:
	bool notify();
	void notifyAll();

private:
	std::queue<RTOS::task*> blocked{};
};


#endif //PROJECT_EVENTGENERATOR_H
