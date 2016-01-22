//
// Created by chiel on 21/01/16.
//

#include "EventGenerator.h"

void EventGenerator::wait(RTOS::task *user) {
	blocked.push(user);
	user->suspend();
}

bool EventGenerator::notify() {
	if (blocked.empty()) {
		return false;
	} else {
		blocked.front()->resume();
		blocked.pop();
		return true;
	}
}

void EventGenerator::notifyAll() {
	while (notify());
}
