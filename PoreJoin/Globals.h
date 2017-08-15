#ifndef GLOBALS_H
#define GLOBALS_H

#include <fstream>


#define MAX_STRING_LENGTH 1024
#define MAX_PATH_LENGTH 4096

typedef double FloatType;



enum ElementType {PORE, THROAT};

class Pore;
class Throat;
class ElementList;
class PoreNetwork;

extern unsigned int MainNx, MainNy, MainNz;
extern unsigned int TotalNetworks;
extern PoreNetwork *Networks;

void TerM(char *);
void NormalFinish(void);
void RecursiveSweepForConnection(FluidType);
#endif