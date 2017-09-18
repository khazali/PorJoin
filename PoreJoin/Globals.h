#ifndef GLOBALS_H
#define GLOBALS_H

#include <fstream>


#define MAX_STRING_LENGTH 1024
#define MAX_PATH_LENGTH 4096

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
extern unsigned int *DXs, *DYs, *DZs;
extern unsigned int *SumDXs, *SumDYs, *SumDZs;
extern unsigned int *SumPoreNO, *SumThroatNO;
extern PoreNetwork GeneralNetwork;
extern unsigned int MaxThroatNO;
extern FloatType ***StatMatrix;
extern FloatType LengthTotalSD, LengthTotalAve, RadiusTotalSD, RadiusTotalAve;

void TerM(char *);
void NormalFinish(void);
void UpdatePoresLocation(void);
void ReadInput(char *);
#endif