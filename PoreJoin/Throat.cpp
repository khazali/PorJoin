#include <math.h>
#include "Throat.h"
#include "Pore.h"
#include "MIfstream.h"
#include "ElementList.h"


Throat::Throat(void) {

}
void Throat::ReadLink1(MIfstream& InputFile, Pore *pores, ElementList InletThroats, ElementList OutletThroats) {
	char str[MAX_STRING_LENGTH];
	register int i, j;
	FloatType Z0, Z1;

	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	i=atoi(str);
	switch (i) {
		case -1:
			//IOStat=-1;
			ConnectingPores[0]=NULL;
			Z0=0;
			InletThroats.AddElement(Index);
			break;
		case 0:
			//IOStat=0;
			ConnectingPores[0]=NULL;
			Z0=0;
			OutletThroats.AddElement(Index);
			break;
		default:
			//IOStat=1;
			ConnectingPores[0]=&pores[i-1];
			Z0=pores[i-1].GetZ();			
	}	
	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	j=atoi(str);
	switch (j) {
		case -1:
			//IOStat=-1;
			ConnectingPores[1]=NULL;
			Z1=0;
			InletThroats.AddElement(Index);
			break;
		case 0:
			//IOStat=0;
			ConnectingPores[1]=NULL;
			Z1=0;
			OutletThroats.AddElement(Index);
			break;
		default:
			//IOStat=1;
			ConnectingPores[1]=&pores[j-1];
			Z1=pores[j-1].GetZ();
	}
	if (Z0 && Z1) Z=(Z0+Z1)/2;
	else Z=Z0+Z1;

	if ((i==(-1)) || (j==(-1))) IOStat=-1;
	else if ((i==0) || (j==0)) IOStat=0;
	else IOStat=1;

	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	InscribedRadius=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	ShapeFactor=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	TotalLength=atof(str);
}

void Throat::ReadLink2(MIfstream& InputFile) {
	char str[MAX_STRING_LENGTH];

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	if (ConnectingPores[0]!=NULL) ConnectingPores[0]->SetLength(atof(str));

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	if (ConnectingPores[1]!=NULL) ConnectingPores[1]->SetLength(atof(str));

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	Length=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	Volume=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	ClayVolume=atof(str);
}

void Throat::SweepAdjacentPores(FluidType Fluid) {
	if ((ConnectingPores[0]!=NULL) && (!ConnectingPores[0]->GetIsVisited()) && (((Fluid==OIL) && (ConnectingPores[0]->GetIsOilFilled())) || ((Fluid==WATER) && (ConnectingPores[0]->GetWaterCoatingExist()))) && (ConnectingPores[0]->GetIsEnabled())) {
		ConnectingPores[0]->SetIsVisited(true);
		ConnectingPores[0]->SetIsConnectedToOutlet(Fluid, true);
		ConnectingPores[0]->SweepAdjacentThroats(Fluid);
	}
	if ((ConnectingPores[1]!=NULL) && (!ConnectingPores[1]->GetIsVisited()) && (((Fluid==OIL) && (ConnectingPores[1]->GetIsOilFilled())) || ((Fluid==WATER) && (ConnectingPores[1]->GetWaterCoatingExist()))) && (ConnectingPores[1]->GetIsEnabled())) {
		ConnectingPores[1]->SetIsVisited(true);
		ConnectingPores[1]->SetIsConnectedToOutlet(Fluid, true);
		ConnectingPores[1]->SweepAdjacentThroats(Fluid);
	}	
}

FloatType Throat::GetTotalLength(void){
	return TotalLength;
}

void Throat::SweepAdjacentPoresForDeletion(ExitType mExit) {
	if (mExit == OUTLET) {
		if ((ConnectingPores[0] != NULL) && (!ConnectingPores[0]->GetIsVisited())) {
			ConnectingPores[0]->SetIsVisited(true);
			ConnectingPores[0]->SetIsConnectedToOutlet(WATER, true);
			ConnectingPores[0]->SweepAdjacentThroatsForDeletion(OUTLET);
		}
		if ((ConnectingPores[1] != NULL) && (!ConnectingPores[1]->GetIsVisited())) {
			ConnectingPores[1]->SetIsVisited(true);
			ConnectingPores[1]->SetIsConnectedToOutlet(WATER, true);
			ConnectingPores[1]->SweepAdjacentThroatsForDeletion(OUTLET);
		}
	}
	else {
		if ((ConnectingPores[0] != NULL) && (!ConnectingPores[0]->GetIsVisited())) {
			ConnectingPores[0]->SetIsVisited(true);
			ConnectingPores[0]->SetIsConnectedToInlet(true);
			ConnectingPores[0]->SweepAdjacentThroatsForDeletion(INLET);
		}
		if ((ConnectingPores[1] != NULL) && (!ConnectingPores[1]->GetIsVisited())) {
			ConnectingPores[1]->SetIsVisited(true);
			ConnectingPores[1]->SetIsConnectedToInlet(true);
			ConnectingPores[1]->SweepAdjacentThroatsForDeletion(INLET);
		}
	}
	
}

int Throat::GetIOStat(void) {
	return IOStat;
}