#ifndef SWIRLI_WASHINGCONTROLLER_H
#define SWIRLI_WASHINGCONTROLLER_H

class WashingController {
public:
	WashingController(LogController &log);

	void start(WashingProgram &program);

private:
	/**
	 * return the washing machine to the state ready for sleep.
	 * this includes doing things like:
	 * - pumping away water
	 * - disabling temperature control
	 * - stopping logging
	 * - other things
	 */
	void endProgram();
};

#endif