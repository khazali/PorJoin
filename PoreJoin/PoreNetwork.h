#pragma once
#include "Pore.h"
#include "Throat.h"
#include "ElementList.h"
#include "Globals.h"


class PoreNetwork {
private:
	Pore *pores;
	Throat *throats;
	unsigned int PoreNO, ThroatNO;
	FloatType Dx, Dy, Dz;				//Dimensions of the porous media
	ElementList OutletThroats, InletThroats;
	unsigned int *PorePointer, *ThroatPointer;
	
	FloatType MinX, MinY, MinZ;

	PoreNetwork *X_Before;
	PoreNetwork *X_After;
	PoreNetwork *Y_Before;
	PoreNetwork *Y_After;
	PoreNetwork *Z_Before;
	PoreNetwork *Z_After;

public:
	void ReadStatoilFormat(char *, char *);
	PoreNetwork();
	~PoreNetwork();
	void SetNeighbours(PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *);
};