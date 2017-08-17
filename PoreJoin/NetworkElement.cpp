#include "NetworkElement.h"
#include "Globals.h"
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <iostream>

void NetworkElement::SetIndex(unsigned int ElementIndex) {
	Index=ElementIndex;
}

NetworkElement::NetworkElement(void) {
	IsEnabled = true;
}

void NetworkElement::SetIsConnectedToOutlet(FluidType Fluid, bool ConnectionStatus) {
	IsConnectedToOutlet = ConnectionStatus;	
}
bool NetworkElement::GetIsConnectedToOutlet(FluidType Fluid) {
	return IsConnectedToOutlet;
}

void NetworkElement::SetIsConnectedToInlet(bool ConnectionStatus) {
	IsConnectedToInlet = ConnectionStatus;
}
bool NetworkElement::GetIsConnectedToInlet(void) {
	return IsConnectedToInlet;
}

void NetworkElement::SetIsVisited(bool VisitStatus) {
	IsVisited=VisitStatus;
}
bool NetworkElement::GetIsVisited(void) {	
	return IsVisited;
}

FloatType NetworkElement::GetLength(void){
	return Length;
}

FloatType NetworkElement::GetZ(void) {
	return Z;
}
unsigned int NetworkElement::GetIndex(void) {
	return Index;
}

bool NetworkElement::GetIsEnabled(void) {
	return IsEnabled;
}

void NetworkElement::SetIsEnabled(bool EnableStat) {
	IsEnabled = EnableStat;
}