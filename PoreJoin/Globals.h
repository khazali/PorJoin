#ifndef GLOBALS_H
#define GLOBALS_H

#include <fstream>


#define MAX_STRING_LENGTH 1024
#define MAX_PATH_LENGTH 4096

typedef double FloatType;



enum ElementType {PORE, THROAT};
enum ImbibitionType {SPONTANEOUS, FORCED};
enum SortType {DESCENDING, ASCENDING};
enum ProcessType {DRAINAGE, IMBIBITION};
enum FluidType {WATER, OIL};
enum ExitType {INLET, OUTLET};

class Pore;
class Throat;
class ElementList;

extern Pore *pores;
extern Throat *throats;
extern ElementList OutletThroats, InletThroats;

extern FloatType Dx, Dy, Dz;				//Dimensions of the porous media
extern unsigned int PoreNO, ThroatNO;
extern unsigned int MainNx, MainNy, MainNz;

void TerM(char *);
void NormalFinish(void);
void ReadStatoilFormat(char *, char *, std::ofstream&, std::ofstream&);
void RecursiveSweepForConnection(FluidType);
#endif