//
// Created by chiel on 21/01/16.
//

#include "EventGenerator.h"

EventGenerator::EventGenerator(RTOS::task *parent):
		flag{parent},
		waiting{} {
	waiting.write(0);
}

RTOS::waitable EventGenerator::waitEvent() {
	return flag;
}

bool EventGenerator::notify() {
	int waitNum{waiting.read()};
	if (waitNum > 0) {
		waiting.write(--waitNum);
		flag.set();
		return true;
	} else {
		return false;
	}
}

void EventGenerator::notifyAll() {
	while (notify());
}
