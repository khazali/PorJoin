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
	//Pore** AdjacentPores;
	//Throat** ConnectingThroats;
	FloatType X, Y, Z;					//Pore location coordinates	
	//unsigned int MatrixPlace;	

	int *PoreIndexes, *ThroatIndexes;
	unsigned int Primary_Index;
	
public:
	Pore();
	~Pore();
	void SetLength(FloatType);
	void ReadNode1(MIfstream&, Pore *, Throat*);
	void ReadNode2(MIfstream&);	
	unsigned int GetCoordinationNumber(void);	
	void UpdateLocation(FloatType, FloatType, FloatType);
	void UpdatePoreIndexes(unsigned int, unsigned int);
	void SetProperties(unsigned int, FloatType, FloatType, FloatType, unsigned int, int, FloatType, FloatType, FloatType, FloatType, FloatType, bool, unsigned int);
	void GetProperties(unsigned int&, FloatType &, FloatType &, FloatType &, unsigned int &, int &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &);
	void SetConnectingPoreAndThroats(int *, int *);
	void GetConnectingPoreAndThroats(int *, int *);
	void GetNumberedConnectingPoreAndThroats(unsigned int, int &, int &);
	void SetCoordinationNumber(unsigned int);
	unsigned int GetPrimaryIndex(void);
	FloatType GetX(void);
	FloatType GetY(void);
	FloatType GetZ(void);
	void AddThroat(int, int);
	void WriteNeighbours(std::ofstream &);
	void DelBranch(unsigned int);
	void UpdateConnectingThroatIndexes(unsigned int *);
};
#endif