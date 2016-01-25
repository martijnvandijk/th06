//
// Created by chiel on 18/01/16.
//

#include "AddSoapInstruction.h"

AddSoapInstruction::AddSoapInstruction(WashingMachine::SoapDispenser &dispenser) :
		dispenser(dispenser) { }

void AddSoapInstruction::execute(WashingProgramRunner &runner, LogController &logController, bool doWait) {
	dispenser.set(WashingMachine::SOAP_OPEN, &runner);
}
