#pragma once
#include "Pore.h"
#include "Throat.h"
#include "ElementList.h"


class PoreNetwork {
private:
	Pore *pores;
	Throat *throats;
	unsigned int PoreNO, ThroatNO;
	FloatType Dx, Dy, Dz;				//Dimensions of the porous media
	ElementList OutletThroats, InletThroats;
	unsigned int *PorePointer, *ThroatPointer;

public:
	void ReadStatoilFormat(char *, char *, std::ofstream&, std::ofstream&);
	PoreNetwork();
	~PoreNetwork();
};