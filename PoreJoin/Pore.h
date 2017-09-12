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

	int *PoreIndexes, *ThroatIndexes;
	
public:
	Pore();
	~Pore();
	void SetLength(FloatType);
	unsigned int ReadNode1(MIfstream&, Pore *, Throat*);
	void ReadNode2(MIfstream&);	
	unsigned int GetCoordinationNumber(void);
	bool IsConnectedThroatNull(unsigned int);	
	unsigned int NumberOfConnections(void);	
	void UpdateLocation(FloatType, FloatType, FloatType);
	void UpdatePoreIndexes(unsigned int, unsigned int);
	void SetProperties(unsigned int, FloatType, FloatType, FloatType, unsigned int, int, FloatType, FloatType, FloatType, FloatType, FloatType, bool);
	void GetProperties(unsigned int&, FloatType &, FloatType &, FloatType &, unsigned int &, int &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &);
	void SetConnectingPoreAndThroats(int *, int *);
	void GetConnectingPoreAndThroats(int *, int *);
};
#endif