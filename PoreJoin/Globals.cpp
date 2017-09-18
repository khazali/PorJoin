#include "Globals.h"

unsigned int MainNx, MainNy, MainNz;
unsigned int TotalNetworks;
unsigned int *DXs, *DYs, *DZs;
unsigned int *SumDXs, *SumDYs, *SumDZs;
unsigned int *SumPoreNO, *SumThroatNO;
unsigned int MaxThroatNO;
FloatType ***StatMatrix;
FloatType LengthTotalSD, LengthTotalAve, RadiusTotalSD, RadiusTotalAve;

PoreNetwork *Networks;
PoreNetwork GeneralNetwork;