#ifndef GLOBALS_H
#define GLOBALS_H

#include <fstream>


#define MAX_STRING_LENGTH 1024
#define MAX_PATH_LENGTH 4096
#define USE_GLOBAL_DISTRIBUTION false
#define CONNECTION_FRACTION 0.1
//#define SQRT_2PI 2.506628274631000502415765284811
#define SIMPSON_1_3_INTEGRATION 1000
#define MAX_THROATS_COEFFICIENT 2
#define PI 3.1415926535897932384626433832795

typedef double FloatType;



enum ElementType {PORE, THROAT};
class NetworkElement;
class PoreNetwork;
class MIfstream;
class Pore;
class Throat;
class ElementList;



extern unsigned int MainNx, MainNy, MainNz;
extern unsigned int TotalNetworks;
extern PoreNetwork *Networks;
extern FloatType *DXs, *DYs, *DZs;
extern FloatType *SumDXs, *SumDYs, *SumDZs;
extern unsigned int *SumPoreNO, *SumThroatNO;
extern PoreNetwork GeneralNetwork;
extern unsigned int MaxThroatNO;
extern FloatType ***StatMatrix;
extern FloatType LengthTotalSD, LengthTotalAve, RadiusTotalSD, RadiusTotalAve;
extern FloatType MaxLength, MinLength, MaxRadius, MinRadius;
extern char ResultPath[MAX_PATH_LENGTH];

void TerM(char *);
void NormalFinish(void);
void UpdatePoresLocation(void);
void ReadInput(char *);
bool NormalSelect(FloatType, FloatType, FloatType, FloatType, FloatType);
FloatType NormRand(FloatType, FloatType, FloatType, FloatType);
void UpdateIndexes(void);
void CalculateStatistics(void);
void ReadInput(char *);

#endif