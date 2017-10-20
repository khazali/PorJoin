#include <math.h>
#include "PoreNetwork.h"
#include "Pore.h"
#include "MIfstream.h"




Pore::Pore(void) {

}

Pore::~Pore(void) {	
	delete[] PoreIndexes;
	delete[] ThroatIndexes;
}

void Pore::SetLength(FloatType InLength) {
	Length=InLength;
}

void Pore::ReadNode1(MIfstream& InputFile, Pore *pores, Throat* throats){
	char str[MAX_STRING_LENGTH];
	register int j;
	register unsigned int i;


	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	X=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	Y=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	Z=atof(str);

	if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
	CoordinationNumber=atoi(str);

	PoreIndexes = new int[CoordinationNumber];
	ThroatIndexes = new int[CoordinationNumber];

	for (i=0; i<CoordinationNumber; i++) {
		if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
		j=atoi(str);
		PoreIndexes[i] = j;
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
		ThroatIndexes[i] = j;	
	}
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

unsigned int Pore::GetCoordinationNumber(void) {
	return CoordinationNumber;
}

void Pore::UpdateLocation(FloatType X_Origin, FloatType Y_Origin, FloatType Z_Origin) {
	X += X_Origin;
	Y += Y_Origin;
	Z += Z_Origin;
}

void Pore::UpdatePoreIndexes(unsigned int PoreRef) {
	//register unsigned int i;

	Index += PoreRef;
	/*for (i = 0; i < CoordinationNumber; i++) {
		PoreIndexes[i] += PoreRef;
		ThroatIndexes[i] += ThroatRef;
	}*/
}

void Pore::GetProperties(unsigned int &PIndex, FloatType &XLocation, FloatType &YLocation, FloatType &ZLocation, unsigned int &CN, int &IOStatus, FloatType &PoreVolume, FloatType &PoreInscribedRadius, FloatType &PoreShapeFactor, FloatType &PoreClayVolume, FloatType &PoreLength) {
	XLocation = X;
	YLocation = Y;
	ZLocation = Z;
	CN = CoordinationNumber;
	IOStatus = IOStat;
	PoreVolume = Volume;
	PoreInscribedRadius = InscribedRadius;
	PoreShapeFactor = ShapeFactor;
	PoreClayVolume = ClayVolume;
	PoreLength = Length;
	PIndex = Index;
}

void Pore::SetProperties(unsigned int PIndex, FloatType XLocation, FloatType YLocation, FloatType ZLocation, unsigned int CN, int IOStatus, FloatType PoreVolume, FloatType PoreInscribedRadius, FloatType PoreShapeFactor, FloatType PoreClayVolume, FloatType PoreLength, bool DeadEndCondition, unsigned int PrimaryIndex) {
	X = XLocation;
	Y = YLocation;
	Z = ZLocation;
	CoordinationNumber = CN;
	IOStat = IOStatus;
	Volume = PoreVolume;
	InscribedRadius = PoreInscribedRadius;
	ShapeFactor = PoreShapeFactor;
	ClayVolume = PoreClayVolume;
	Length = PoreLength;
	Index = PIndex;
	HasDeadEnds = DeadEndCondition;
	Primary_Index = PrimaryIndex;
}

void Pore::SetConnectingPoreAndThroats(int *PPores, int *PThroats) {
	register unsigned int i;

	PoreIndexes = new int[CoordinationNumber];
	ThroatIndexes = new int[CoordinationNumber];

	for (i = 0; i < CoordinationNumber; i++) {
		PoreIndexes[i] = PPores[i];
		ThroatIndexes[i] = PThroats[i];
	}
}
void Pore::GetConnectingPoreAndThroats(int *PPores, int *PThroats) {
	register unsigned int i;

	for (i = 0; i < CoordinationNumber; i++) {
		PPores[i] = PoreIndexes[i];
		PThroats[i] = ThroatIndexes[i];
	}
}

void Pore::GetNumberedConnectingPoreAndThroats(unsigned int ConnectionIndex, int &PPores, int &PThroats) {
    PPores = PoreIndexes[ConnectionIndex];
	PThroats = ThroatIndexes[ConnectionIndex];
}

void Pore::SetCoordinationNumber(unsigned int CoNumber) {
	CoordinationNumber = CoNumber;
}

unsigned int Pore::GetPrimaryIndex(void) {
	return Primary_Index;
}

FloatType Pore::GetX(void) {
	return X;
}
FloatType Pore::GetY(void) {
	return Y;
}

FloatType Pore::GetZ(void) {
	return Z;
}

void Pore::AddThroat(int ThroatIndex, int OtherPoreIndeex) {
	int *PoreIndexesCopy, *ThroatIndexesCopy;
	register unsigned int i;

	PoreIndexesCopy = new int[CoordinationNumber];
	ThroatIndexesCopy = new int[CoordinationNumber];

	for (i = 0; i < CoordinationNumber; i++) {
		PoreIndexesCopy[i] = PoreIndexes[i];
		ThroatIndexesCopy[i] = ThroatIndexes[i];
	}
	delete[] PoreIndexes;
	delete[] ThroatIndexes;
	PoreIndexes = NULL;
	ThroatIndexes = NULL;

	CoordinationNumber++;
	PoreIndexes = new int[CoordinationNumber];
	ThroatIndexes = new int[CoordinationNumber];
	for (i = 0; i < (CoordinationNumber - 1); i++) {
		PoreIndexes[i] = PoreIndexesCopy[i];
		ThroatIndexes[i] = ThroatIndexesCopy[i];
	}
	PoreIndexes[CoordinationNumber - 1] = OtherPoreIndeex;
	ThroatIndexes[CoordinationNumber - 1] = ThroatIndex;

	delete[] PoreIndexesCopy;
	delete[] ThroatIndexesCopy;
}

void Pore::WriteNeighbours(std::ofstream &Output) {
	register unsigned int i;

	for (i = 0; i < CoordinationNumber; i++) Output << PoreIndexes[i] << '\t';

	switch (IOStat) {
	case -1:
		Output << 1 << '\t' << 0 << '\t';
		break;
	case 0:
		Output << 0 << '\t' << 1 << '\t';
		break;
	case 1:
		Output << 0 << '\t' << 0 << '\t';
		break;
	}

	for (i = 0; i < CoordinationNumber; i++) Output << ThroatIndexes[i] << '\t';
}

void Pore::DelBranch(unsigned int Branch) {
	register unsigned int i;

	CoordinationNumber--;
	for (i = Branch; i < CoordinationNumber; i++) {
		PoreIndexes[i] = PoreIndexes[i + 1];
		ThroatIndexes[i] = ThroatIndexes[i + 1];
	}
}

void Pore::UpdateConnectingThroatIndexes(unsigned int *UpdatePointer) {
	register unsigned int i;

	for (i = 0; i < CoordinationNumber; i++) ThroatIndexes[i] = UpdatePointer[ThroatIndexes[i] - 1] + 1;
}