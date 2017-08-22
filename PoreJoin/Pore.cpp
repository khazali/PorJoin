#include <math.h>
#include "PoreNetwork.h"
#include "Pore.h"
#include "MIfstream.h"




Pore::Pore(void) {

}

Pore::~Pore(void) {
	delete[] AdjacentPores;	
	delete[] ConnectingThroats;		
}

void Pore::SetLength(FloatType InLength) {
	Length=InLength;
}

unsigned int Pore::ReadNode1(MIfstream& InputFile, Pore *pores, Throat* throats){
	char str[MAX_STRING_LENGTH];
	register int j;
	register unsigned int i, Nulls;

	Nulls=0;

	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	X=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	Y=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	Z=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	CoordinationNumber=atoi(str);

	AdjacentPores=new Pore* [CoordinationNumber];
	ConnectingThroats=new Throat* [CoordinationNumber];

	for (i=0; i<CoordinationNumber; i++) {
		if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
		j=atoi(str);
		if (j>0) AdjacentPores[i]=&pores[j-1];
		else {
			AdjacentPores[i]=NULL;
			Nulls++;
		}
	}

	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	i=atoi(str);
	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	j=atoi(str);
	if (i==1) IOStat=-1;
	else if (j==1) IOStat=0;
	else IOStat=1;

	for (i=0; i<CoordinationNumber; i++) {
		if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
		j=atoi(str);
		if (j>0) ConnectingThroats[i]=&throats[j-1];
		else ConnectingThroats[i]=NULL;		
	}

	return CoordinationNumber-Nulls;
}
void Pore::ReadNode2(MIfstream& InputFile){
	char str[MAX_STRING_LENGTH];

	if (!InputFile.ReadWord(str)) TerM("Incorrect node2 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect node2 file format!");
	Volume=atof(str);	

	if (!InputFile.ReadWord(str)) TerM("Incorrect node2 file format!");
	InscribedRadius=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect node2 file format!");
	ShapeFactor=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect node2 file format!");
	ClayVolume=atof(str);
}

void Pore::SweepAdjacentThroats(FluidType Fluid) {
	register unsigned int i;
	for (i=0; i<CoordinationNumber; i++) {
		if ((ConnectingThroats[i]!=NULL) && (!ConnectingThroats[i]->GetIsVisited()) && (((Fluid==OIL) || (ConnectingThroats[i]->GetIsOilFilled())) || ((Fluid==WATER) || (ConnectingThroats[i]->GetWaterCoatingExist()))) && (ConnectingThroats[i]->GetIsEnabled())) {
			ConnectingThroats[i]->SetIsVisited(true);
			ConnectingThroats[i]->SetIsConnectedToOutlet(Fluid, true);
			ConnectingThroats[i]->SweepAdjacentPores(Fluid);
		}
	}
}

void Pore::SweepAdjacentThroatsForDeletion(ExitType mExit) {
	register unsigned int i;

	if (mExit == OUTLET) {
		for (i = 0; i < CoordinationNumber; i++) {
			if ((ConnectingThroats[i] != NULL) && (!ConnectingThroats[i]->GetIsVisited())) {
				ConnectingThroats[i]->SetIsVisited(true);
				ConnectingThroats[i]->SetIsConnectedToOutlet(WATER, true);
				ConnectingThroats[i]->SweepAdjacentPoresForDeletion(OUTLET);
			}
		}
	}
	else {
		for (i = 0; i < CoordinationNumber; i++) {
			if ((ConnectingThroats[i] != NULL) && (!ConnectingThroats[i]->GetIsVisited())) {
				ConnectingThroats[i]->SetIsVisited(true);
				ConnectingThroats[i]->SetIsConnectedToInlet(true);
				ConnectingThroats[i]->SweepAdjacentPoresForDeletion(INLET);
			}
		}
	}
	
}

unsigned int Pore::GetCoordinationNumber(void) {
	return CoordinationNumber;
}

bool Pore::IsConnectedThroatNull(unsigned int AdjacentPoresIndex) {
	return (AdjacentPores[AdjacentPoresIndex] == NULL);
}

unsigned int Pore::NumberOfConnections(void) {
	register unsigned int i, j;

	j = 0;
	for (i = 0; i < CoordinationNumber; i++) if (AdjacentPores[i] != NULL) j++;
	return j;
}

void Pore::CalibrateCoordinates(FloatType MinX, FloatType MinY, FloatType MinZ) {
	X -= MinX;
	Y -= MinY;
	Z -= MinZ;
}