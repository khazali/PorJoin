#include <math.h>
#include "Globals.h"

#include "MIfstream.h"
#include "Throat.h"
#include "Pore.h"
//#include "ElementList.h"


Throat::Throat(void) {

}
void Throat::ReadLink1(MIfstream& InputFile) {
	char str[MAX_STRING_LENGTH];
	register int i, j;
	

	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	i=atoi(str);
	switch (i) {
		case -1:
			//IOStat=-1;
			//ConnectingPores[0]=NULL;
			Pore1Index = -1;
			//InletThroats.AddElement(Index);
			break;
		case 0:
			//IOStat=0;
			//ConnectingPores[0]=NULL;
			Pore1Index = 0;
			//OutletThroats.AddElement(Index);
			break;
		default:
			//IOStat=1;
			//ConnectingPores[0]=&pores[i-1];
			Pore1Index = i;
	}	
	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	j=atoi(str);
	switch (j) {
		case -1:
			//IOStat=-1;
			//ConnectingPores[1]=NULL;
			Pore2Index = -1;
			//InletThroats.AddElement(Index);
			break;
		case 0:
			//IOStat=0;
			//ConnectingPores[1]=NULL;
			Pore2Index = 0;
			//OutletThroats.AddElement(Index);
			break;
		default:
			//IOStat=1;
			//ConnectingPores[1]=&pores[j-1];
			Pore2Index = j;
	}	

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

void Throat::ReadLink2(MIfstream& InputFile, Pore *pores) {
	char str[MAX_STRING_LENGTH];

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	if (Pore1Index > 0) pores[Pore1Index - 1].SetLength(atof(str));

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	if (Pore2Index > 0) pores[Pore2Index - 1].SetLength(atof(str));

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	Length=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	Volume=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect link2 file format!");
	ClayVolume=atof(str);
}

FloatType Throat::GetTotalLength(void){
	return TotalLength;
}

int Throat::GetIOStat(void) {
	return IOStat;
}

int Throat::GetPore1Index(void) {
	return Pore1Index;
}

int Throat::GetPore2Index(void) {
	return Pore2Index;
}

void Throat::UpdateThroatIndexes(unsigned int PoreRef, unsigned int ThroatRef) {
	Index += ThroatRef;
	//Pore1Index += PoreRef;
	//Pore2Index += PoreRef;	
}

void Throat::GetProperties(unsigned int &ThroatIndex, int &Pore1Pointer, int &Pore2Pointer, int &IOStatus, FloatType &ThroatInscribedRadius, FloatType &ThroatShapeFactor, FloatType &ThroatTotalLength, FloatType &ThroatLength, FloatType &ThroatVolume, FloatType &ThroatClayVolume) {
	Pore1Pointer = Pore1Index;
	Pore2Pointer = Pore2Index;
	IOStatus = IOStat;
	InscribedRadius = ThroatInscribedRadius;
	ShapeFactor = ThroatShapeFactor;
	ThroatTotalLength = TotalLength;
	ThroatLength = Length;
	ThroatVolume = Volume;
	ThroatClayVolume = ClayVolume;
	ThroatIndex = Index;
}

void Throat::GetPropertiesWithDeadEnd(unsigned int &ThroatIndex, int &Pore1Pointer, int &Pore2Pointer, int &IOStatus, FloatType &ThroatInscribedRadius, FloatType &ThroatShapeFactor, FloatType &ThroatTotalLength, FloatType &ThroatLength, FloatType &ThroatVolume, FloatType &ThroatClayVolume, bool &DeadEndCondition) {
	Pore1Pointer = Pore1Index;
	Pore2Pointer = Pore2Index;
	IOStatus = IOStat;
	InscribedRadius = ThroatInscribedRadius;
	ShapeFactor = ThroatShapeFactor;
	ThroatTotalLength = TotalLength;
	ThroatLength = Length;
	ThroatVolume = Volume;
	ThroatClayVolume = ClayVolume;
	ThroatIndex = Index;
	DeadEndCondition = HasDeadEnds;
}


void Throat::SetProperties(unsigned int ThroatIndex, int Pore1Pointer, int Pore2Pointer, int IOStatus, FloatType ThroatInscribedRadius, FloatType ThroatShapeFactor, FloatType ThroatTotalLength, FloatType ThroatLength, FloatType ThroatVolume, FloatType ThroatClayVolume, bool DeadEndCondition) {
	Pore1Index = Pore1Pointer;
	Pore2Index = Pore2Pointer;
	IOStat = IOStatus;
	ThroatInscribedRadius = InscribedRadius;
	ThroatShapeFactor = ShapeFactor;
	TotalLength = ThroatTotalLength;
	Length = ThroatLength;
	Volume = ThroatVolume;
	ClayVolume = ThroatClayVolume;
	Index = ThroatIndex;
	HasDeadEnds = DeadEndCondition;
}

FloatType Throat::GetInscribedRadius(void) {
	return InscribedRadius;
}