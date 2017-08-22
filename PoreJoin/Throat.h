#ifndef THROAT_H
#define THROAT_H
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "MIfstream.h"
#include "Globals.h"
#include "NetworkElement.h"


class Throat: public NetworkElement {
private:
	Pore *ConnectingPores[2];
	FloatType TotalLength;		//Throat Total Length (pore center to pore center)
	FloatType WaterConductancePerLength, OilConductancePerLength, TotalConductancePerLength;
	FloatType OilVelocity, WaterVelocity;

public:
	Throat();
	void ReadLink1(MIfstream&, Pore *, ElementList, ElementList);
	void ReadLink2(MIfstream&);
	void SweepAdjacentPores(FluidType);
	FloatType GetTotalLength(void);
	void SweepAdjacentPoresForDeletion(ExitType);
	int GetIOStat(void);
};

#endif