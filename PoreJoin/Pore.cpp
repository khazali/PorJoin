#include <math.h>
#include "PoreNetwork.h"
#include "Pore.h"
#include "MIfstream.h"




Pore::Pore(void) {

}

Pore::~Pore(void) {
	delete[] AdjacentPores;	
	delete[] ConnectingThroats;
	delete[] PoreIndexes;
	delete[] ThroatIndexes;
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
	PoreIndexes = new int[CoordinationNumber];
	ThroatIndexes = new int[CoordinationNumber];

	for (i=0; i<CoordinationNumber; i++) {
		if (!InputFile.ReadWord(str)) TerM("Incorrect node1 file format!");
		j=atoi(str);
		PoreIndexes[i] = j;
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
		ThroatIndexes[i] = j;
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

void Pore::UpdateLocation(FloatType X_Origin, FloatType Y_Origin, FloatType Z_Origin) {
	X += X_Origin;
	Y += Y_Origin;
	Z += Z_Origin;
}

void Pore::UpdatePoreIndexes(unsigned int PoreRef, unsigned int ThroatRef) {
	register unsigned int i, Terminations;

	Terminations = 0;
	Index += PoreRef;
	for (i = 0; (i+Terminations) < CoordinationNumber; i++) {
		if (PoreIndexes[i+Terminations]) PoreIndexes[i-Terminations] += PoreRef;
		else {
			if (IOStat == 1) Terminations++;
		}
		ThroatIndexes[i] += ThroatRef;
	}
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

void Pore::SetProperties(unsigned int PIndex, FloatType XLocation, FloatType YLocation, FloatType ZLocation, unsigned int CN, int IOStatus, FloatType PoreVolume, FloatType PoreInscribedRadius, FloatType PoreShapeFactor, FloatType PoreClayVolume, FloatType PoreLength) {
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
}

void Pore::SetConnectingPoreAndThroats(int *PPores, int*PThroats) {
	register int i;

	PoreIndexes = new int[CoordinationNumber];
	ThroatIndexes = new int[CoordinationNumber];

	for (i = 0; i < CoordinationNumber; i++) {
		PoreIndexes[i] = PPores[i];
		ThroatIndexes[i] = PThroats[i];
	}
}
void Pore::GetConnectingPoreAndThroats(int *PPores, int*PThroats) {
	register int i;

	for (i = 0; i < CoordinationNumber; i++) {
		PPores[i] = PoreIndexes[i];
		PThroats[i] = ThroatIndexes[i];
	}
}
