//
// Created by chiel on 18/01/16.
//

#include "AddSoapInstruction.h"

AddSoapInstruction::AddSoapInstruction(WashingMachine::SoapDispenser &dispenser):
		dispenser(dispenser)
{}

void AddSoapInstruction::execute(WashingMachine::UARTUser *user, LogController &logController) {
	//dispenser.dispense(user);
}
