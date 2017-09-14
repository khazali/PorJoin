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

void NetworkElement::SetNetworkIndex(unsigned int XIndex, unsigned int YIndex, unsigned int ZIndex) {
	NetworkIndex_X = XIndex;
	NetworkIndex_Y = YIndex;
	NetworkIndex_Z = ZIndex;
}

void NetworkElement::GetNetworkIndex(unsigned int &XIndex, unsigned int &YIndex, unsigned int &ZIndex) {
	XIndex = NetworkIndex_X;
	YIndex = NetworkIndex_Y;
	ZIndex = NetworkIndex_Z;
}

void NetworkElement::SetDeadEnds(bool DeadEndCondition) {
	HasDeadEnds = DeadEndCondition;
}
bool NetworkElement::GetDeadEnds(void) {
	return HasDeadEnds;
}