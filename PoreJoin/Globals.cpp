#include "Globals.h"
#include "PoreNetwork.h"

unsigned int MainNx, MainNy, MainNz;
unsigned int TotalNetworks;
FloatType *DXs, *DYs, *DZs;
FloatType *SumDXs, *SumDYs, *SumDZs;
unsigned int *SumPoreNO, *SumThroatNO;
unsigned int MaxThroatNO, MaxPoreNO;
FloatType ***StatMatrix;
FloatType LengthTotalSD, LengthTotalAve, RadiusTotalSD, RadiusTotalAve, CoNOAve, CoNOSD;
FloatType MaxLength, MinLength, MaxRadius, MinRadius, CoNOMin, CoNOMax;
FloatType ConnectionFraction;
FloatType LIntegral, CIntegral;

PoreNetwork *Networks;
PoreNetwork GeneralNetwork;

char ResultPath[MAX_PATH_LENGTH];