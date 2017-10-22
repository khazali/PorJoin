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
			Pore1Index = -1;
			break;
		case 0:
			//IOStat=0;
			Pore1Index = 0;
			break;
		default:
			//IOStat=1;
			Pore1Index = i;
	}	
	if (!InputFile.ReadWord(str)) TerM("Incorrect link1 file format!");
	j=atoi(str);
	switch (j) {
		case -1:
			//IOStat=-1;
			Pore2Index = -1;
			break;
		case 0:
			//IOStat=0;
			Pore2Index = 0;
			break;
		default:
			//IOStat=1;
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

void Throat::UpdateThroatIndexes(unsigned int ThroatRef) {
	Index += ThroatRef;	
}

void Throat::GetProperties(unsigned int &ThroatIndex, int &Pore1Pointer, int &Pore2Pointer, int &IOStatus, FloatType &ThroatInscribedRadius, FloatType &ThroatShapeFactor, FloatType &ThroatTotalLength, FloatType &ThroatLength, FloatType &ThroatVolume, FloatType &ThroatClayVolume) {
	Pore1Pointer = Pore1Index;
	Pore2Pointer = Pore2Index;
	IOStatus = IOStat;
	ThroatInscribedRadius = InscribedRadius;
	ThroatShapeFactor = ShapeFactor;
	ThroatTotalLength = TotalLength;
	ThroatLength = Length;
	ThroatVolume = Volume;
	ThroatClayVolume = ClayVolume;
	ThroatIndex = Index;
}

void Throat::SetProperties(unsigned int ThroatIndex, int Pore1Pointer, int Pore2Pointer, int IOStatus, FloatType ThroatInscribedRadius, FloatType ThroatShapeFactor, FloatType ThroatTotalLength, FloatType ThroatLength, FloatType ThroatVolume, FloatType ThroatClayVolume) {
	Pore1Index = Pore1Pointer;
	Pore2Index = Pore2Pointer;
	IOStat = IOStatus;
	InscribedRadius = ThroatInscribedRadius;
	ShapeFactor = ThroatShapeFactor;
	TotalLength = ThroatTotalLength;
	Length = ThroatLength;
	Volume = ThroatVolume;
	ClayVolume = ThroatClayVolume;
	Index = ThroatIndex;
}

FloatType Throat::GetInscribedRadius(void) {
	return InscribedRadius;
}