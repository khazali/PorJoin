#include "Globals.h"
#include "ElementList.h"

Pore *pores;
Throat *throats;
unsigned int PoreNO, ThroatNO;


FloatType Dx, Dy, Dz;				//Dimensions of the porous media

ElementList OutletThroats, InletThroats;
unsigned int *PorePointer, *ThroatPointer;