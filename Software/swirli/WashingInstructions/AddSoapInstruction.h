//
// Created by chiel on 18/01/16.
//

#ifndef ADDSOAPINSTRUCTION_H
#define ADDSOAPINSTRUCTION_H

#include "../WashingMachine/SoapDispenser.h"
#include "WashingInstruction.h"
#include "../LogController.h"

class AddSoapInstruction: public WashingInstruction {
public:
	AddSoapInstruction(WashingMachine::SoapDispenser &dispenser);

	virtual void execute(WashingMachine::UARTUser *user, LogController &logController) override;

private:
	WashingMachine::SoapDispenser &dispenser;
};


#endif //ADDSOAPINSTRUCTION_H
