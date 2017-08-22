#ifndef PORENETWORK_H
#define PORENETWORK_H

#include "MIfstream.h"
#include "ElementList.h"
#include "NetworkElement.h"
//#include "Globals.h"
#include "Pore.h"
#include "Throat.h"





class PoreNetwork {
private:
	Pore *pores;
	Throat *throats;
	unsigned int PoreNO, ThroatNO;
	FloatType Dx, Dy, Dz;				//Dimensions of the porous media
	ElementList OutletThroats, InletThroats;
	unsigned int *PorePointer, *ThroatPointer;
	
	//FloatType MinX, MinY, MinZ;

	PoreNetwork *X_Before;
	PoreNetwork *X_After;
	PoreNetwork *Y_Before;
	PoreNetwork *Y_After;
	PoreNetwork *Z_Before;
	PoreNetwork *Z_After;
	unsigned int NetworkIndex_X, NetworkIndex_Y, NetworkIndex_Z;

public:
	void ReadStatoilFormat(char *, char *);
	PoreNetwork();
	~PoreNetwork();
	void SetNeighbours(PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *);
	void SetNetworkIndex(unsigned int, unsigned int, unsigned int);
	void GetNetworkIndex(unsigned int&, unsigned int&, unsigned int&);
	FloatType GetXDim(void);
	FloatType GetYDim(void);
	FloatType GetZDim(void);
	FloatType UpdatePoresLocation(FloatType, FloatType, FloatType);
};
#endif