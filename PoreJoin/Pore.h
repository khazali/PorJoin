#ifndef PORE_H
#define PORE_H
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Globals.h"
#include "NetworkElement.h"
#include "MIfstream.h"
#include "Throat.h"

class Pore: public NetworkElement {
private:

	unsigned int CoordinationNumber;
	Pore** AdjacentPores;
	Throat** ConnectingThroats;
	FloatType X, Y, Z;					//Pore location coordinates	
	unsigned int MatrixPlace;
	FloatType Pressure;
	
public:
	Pore();
	~Pore();
	void SetLength(FloatType);
	unsigned int ReadNode1(MIfstream&, Pore *, Throat*);
	void ReadNode2(MIfstream&);	
	void SweepAdjacentThroats(FluidType);
	unsigned int GetCoordinationNumber(void);
	void SweepAdjacentThroatsForDeletion(ExitType);
	bool IsConnectedThroatNull(unsigned int);	
	unsigned int NumberOfConnections(void);	
	void UpdateLocation(FloatType, FloatType, FloatType);
};
#endif