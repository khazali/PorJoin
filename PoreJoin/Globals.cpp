#include "Globals.h"
#include "PoreNetwork.h"

unsigned int MainNx, MainNy, MainNz;
unsigned int TotalNetworks;
FloatType *DXs, *DYs, *DZs;
FloatType *SumDXs, *SumDYs, *SumDZs;
unsigned int *SumPoreNO, *SumThroatNO;
unsigned int MaxThroatNO;
FloatType ***StatMatrix;
FloatType LengthTotalSD, LengthTotalAve, RadiusTotalSD, RadiusTotalAve;
FloatType MaxLength, MinLength, MaxRadius, MinRadius;
FloatType ConnectionFraction;

PoreNetwork *Networks;
PoreNetwork GeneralNetwork;

char ResultPath[MAX_PATH_LENGTH];