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
	//Pore *ConnectingPores[2];
	FloatType TotalLength;		//Throat Total Length (pore center to pore center)
	int Pore1Index, Pore2Index;

public:
	Throat();
	//void ReadLink1(MIfstream&, Pore *, ElementList, ElementList);
	void ReadLink1(MIfstream&, Pore *);
	void ReadLink2(MIfstream&, Pore *);
	FloatType GetTotalLength(void);
	int GetIOStat(void);
	int GetPore1Index(void);
	int GetPore2Index(void);
	void UpdateThroatIndexes(unsigned int, unsigned int);
	void GetProperties(unsigned int &, int &, int &, int &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &);
	void GetPropertiesWithDeadEnd(unsigned int &, int &, int &, int &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &, bool &);	
	void SetProperties(unsigned int, int, int, int, FloatType, FloatType, FloatType, FloatType, FloatType, FloatType, bool);
	FloatType GetInscribedRadius(void);
};

#endif