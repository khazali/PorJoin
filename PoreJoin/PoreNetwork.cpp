#include "PoreNetwork.h"
#include "MIfstream.h"

#include "Globals.h"


PoreNetwork::PoreNetwork(void) {
}

PoreNetwork::~PoreNetwork(void) {
	delete[] pores;
	delete[] throats;
}


void PoreNetwork::ReadStatoilFormat(char *FilePath, char *Prefix) {
	MIfstream ThroatData1, ThroatData2, PoreData1, PoreData2;
	char ThroatData1File[MAX_PATH_LENGTH], ThroatData2File[MAX_PATH_LENGTH], PoreData1File[MAX_PATH_LENGTH], PoreData2File[MAX_PATH_LENGTH];
	char str[MAX_STRING_LENGTH];
	unsigned int sLen, i;


	sLen = (unsigned int)strlen(FilePath);
	/*if (FilePath[sLen - 1] != '\\') {		//MS Windows Path for now
		FilePath[sLen] = '\\';
		sLen++;
	}*/

	i = 0;
	while (Prefix[i]) {
		FilePath[sLen] = Prefix[i];
		sLen++;
		i++;
	}

	FilePath[sLen] = '\0';
	//sLen++;

	//std::cout<<FilePath;

	strcpy_s(ThroatData1File, MAX_PATH_LENGTH - 12, FilePath);
	strcpy_s(ThroatData2File, MAX_PATH_LENGTH - 12, FilePath);
	strcpy_s(PoreData1File, MAX_PATH_LENGTH - 12, FilePath);
	strcpy_s(PoreData2File, MAX_PATH_LENGTH - 12, FilePath);


	ThroatData1File[sLen] = '_';
	ThroatData1File[sLen + 1] = 'l';
	ThroatData1File[sLen + 2] = 'i';
	ThroatData1File[sLen + 3] = 'n';
	ThroatData1File[sLen + 4] = 'k';
	ThroatData1File[sLen + 5] = '1';
	ThroatData1File[sLen + 6] = '.';
	ThroatData1File[sLen + 7] = 'd';
	ThroatData1File[sLen + 8] = 'a';
	ThroatData1File[sLen + 9] = 't';
	ThroatData1File[sLen + 10] = '\0';

	ThroatData2File[sLen] = '_';
	ThroatData2File[sLen + 1] = 'l';
	ThroatData2File[sLen + 2] = 'i';
	ThroatData2File[sLen + 3] = 'n';
	ThroatData2File[sLen + 4] = 'k';
	ThroatData2File[sLen + 5] = '2';
	ThroatData2File[sLen + 6] = '.';
	ThroatData2File[sLen + 7] = 'd';
	ThroatData2File[sLen + 8] = 'a';
	ThroatData2File[sLen + 9] = 't';
	ThroatData2File[sLen + 10] = '\0';

	PoreData1File[sLen] = '_';
	PoreData1File[sLen + 1] = 'n';
	PoreData1File[sLen + 2] = 'o';
	PoreData1File[sLen + 3] = 'd';
	PoreData1File[sLen + 4] = 'e';
	PoreData1File[sLen + 5] = '1';
	PoreData1File[sLen + 6] = '.';
	PoreData1File[sLen + 7] = 'd';
	PoreData1File[sLen + 8] = 'a';
	PoreData1File[sLen + 9] = 't';
	PoreData1File[sLen + 10] = '\0';

	PoreData2File[sLen] = '_';
	PoreData2File[sLen + 1] = 'n';
	PoreData2File[sLen + 2] = 'o';
	PoreData2File[sLen + 3] = 'd';
	PoreData2File[sLen + 4] = 'e';
	PoreData2File[sLen + 5] = '2';
	PoreData2File[sLen + 6] = '.';
	PoreData2File[sLen + 7] = 'd';
	PoreData2File[sLen + 8] = 'a';
	PoreData2File[sLen + 9] = 't';
	PoreData2File[sLen + 10] = '\0';

	ThroatData1.open(ThroatData1File, std::fstream::in);
	if (!ThroatData1.is_open()) TerM("Can not open first throat input file!");
	ThroatData2.open(ThroatData2File, std::fstream::in);
	if (!ThroatData2.is_open()) TerM("Can not open second throat input file!");
	PoreData1.open(PoreData1File, std::fstream::in);
	if (!PoreData1.is_open()) TerM("Can not open first pore input file!");
	PoreData2.open(PoreData2File, std::fstream::in);
	if (!PoreData2.is_open()) TerM("Can not open second pore input file!");


	if (!ThroatData1.ReadWord(str)) TerM("Incorrect link1 file format!");
	ThroatNO = atoi(str);
	if (!PoreData1.ReadWord(str)) TerM("Incorrect node1 file format!");
	PoreNO = atoi(str);
	if (!PoreData1.ReadWord(str)) TerM("Incorrect node1 file format!");
	Dx = atof(str);
	if (!PoreData1.ReadWord(str)) TerM("Incorrect node1 file format!");
	Dy = atof(str);
	if (!PoreData1.ReadWord(str)) TerM("Incorrect node1 file format!");
	Dz = atof(str);

	throats = new Throat[ThroatNO];
	pores = new Pore[PoreNO];

	
	//std::srand((unsigned int) time(NULL));

	for (i = 0; i < PoreNO; i++) {
		pores[i].SetIndex(i);
		pores[i].ReadNode1(PoreData1, pores, throats);
		pores[i].ReadNode2(PoreData2);
		pores[i].SetNetworkIndex(NetworkIndex_X, NetworkIndex_Y, NetworkIndex_Z);
	}
	for (i = 0; i < ThroatNO; i++) {
		throats[i].SetIndex(i);
		throats[i].ReadLink1(ThroatData1, pores, InletThroats, OutletThroats);
		throats[i].ReadLink2(ThroatData2);
		throats[i].SetNetworkIndex(NetworkIndex_X, NetworkIndex_Y, NetworkIndex_Z);
	}



	ThroatData1.close();
	ThroatData2.close();
	PoreData1.close();
	PoreData2.close();
}

void PoreNetwork::SetNeighbours(PoreNetwork *XBefore, PoreNetwork *XAfter, PoreNetwork *YBefore, PoreNetwork *YAfter, PoreNetwork *ZBefore, PoreNetwork *ZAfter) {
	X_Before = XBefore;
	X_After = XAfter;
	Y_Before = YBefore;
	Y_After = YAfter;
	Z_Before = ZBefore;
	Z_After = ZAfter;
}

void PoreNetwork::SetNetworkIndex(unsigned int XIndex, unsigned int YIndex, unsigned int ZIndex) {
	NetworkIndex_X = XIndex;
	NetworkIndex_Y = YIndex;
	NetworkIndex_Z = ZIndex;
}

void PoreNetwork::GetNetworkIndex(unsigned int &XIndex, unsigned int &YIndex, unsigned int &ZIndex) {
	XIndex = NetworkIndex_X;
	YIndex = NetworkIndex_Y;
	ZIndex = NetworkIndex_Z;
}

FloatType PoreNetwork::GetXDim(void) {
	return Dx;
}
FloatType PoreNetwork::GetYDim(void) {
	return Dy;
}
FloatType PoreNetwork::GetZDim(void) {
	return Dz;
}

FloatType PoreNetwork::UpdatePoresLocation(FloatType X_Origin, FloatType Y_Origin, FloatType Z_Origin) {
	register unsigned int i;

	for (i = 0; i < PoreNO; i++) pores[i].UpdateLocation(X_Origin, Y_Origin, Z_Origin);
}

unsigned int PoreNetwork::GetPoreNO(void) {
	return PoreNO;
}
unsigned int PoreNetwork::GetThroatNO(void) {
	return ThroatNO;
}
void PoreNetwork::UpdateElementIndex(unsigned int PorRef, unsigned int ThroatRef) {
	register unsigned int i;

	for (i = 0; i < PoreNO; i++) pores[i].UpdatePoreIndexes(PorRef, ThroatRef);
	for (i = 0; i < ThroatNO; i++) throats[i].UpdateThroatIndexes(PorRef, ThroatRef);
}

void PoreNetwork::GetPoreProperties(unsigned int PIndex, unsigned int &PoreIndex, FloatType &X, FloatType &Y, FloatType &Z, unsigned int &CoordinationNumber, int &IOStat, FloatType &Volume, FloatType &InscribedRadius, FloatType &ShapeFactor, FloatType &ClayVolume, FloatType &Length) {
	pores[PIndex].GetProperties(PoreIndex, X, Y, Z, CoordinationNumber, IOStat, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length);
}

void PoreNetwork::SetPoreProperties(unsigned int PIndex, unsigned int PoreIndex, FloatType X, FloatType Y, FloatType Z, unsigned int CoordinationNumber, int IOStat, FloatType Volume, FloatType InscribedRadius, FloatType ShapeFactor, FloatType ClayVolume, FloatType Length, bool DeadEndCondition) {
	pores[PIndex].SetProperties(PoreIndex, X, Y, Z, CoordinationNumber, IOStat, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length, DeadEndCondition);
}

void PoreNetwork::SetPoreAndThroatsPointers(unsigned int PIndex, int *PPores, int *PThroats) {
	pores[PIndex].SetConnectingPoreAndThroats(PPores, PThroats);
}

void PoreNetwork::GetPoreAndThroatsPointers(unsigned int PIndex, int *PPores, int *PThroats) {
	pores[PIndex].GetConnectingPoreAndThroats(PPores, PThroats);
}

void PoreNetwork::GetThroatProperties(unsigned int TIndex, unsigned int &ThroatIndex, int &Pore1Index, int &Pore2Index, int &IOStat, FloatType &InscribedRadius, FloatType &ShapeFactor, FloatType &TotalLength, FloatType &Length, FloatType &Volume, FloatType &ClayVolume) {
	throats[TIndex].GetProperties(ThroatIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume);
}

void PoreNetwork::SetThroatProperties(unsigned int TIndex, unsigned int ThroatIndex, int Pore1Index, int Pore2Index, int IOStat, FloatType InscribedRadius, FloatType ShapeFactor, FloatType TotalLength, FloatType Length, FloatType Volume, FloatType ClayVolume, bool DeadEndCondition) {
	throats[TIndex].SetProperties(ThroatIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume, DeadEndCondition);
}

void PoreNetwork::CopyFromOthers(PoreNetwork &Source) {
	register unsigned int i;
	FloatType X, Y, Z, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length, TotalLength;
	unsigned int CoordinationNumber, SourcePoreNO, SourceThroatNO, PTIndex, N_X, N_Y, N_Z;;
	int IOStat, Pore1Index, Pore2Index;
	int *AdjacentPores, *ConnectingThroats;
	bool DeadEndCondition;

	SourcePoreNO = Source.GetPoreNO();
	for (i = 0; i < SourcePoreNO; i++) {
		Source.GetPoreProperties(i, PTIndex, X, Y, Z, CoordinationNumber, IOStat, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length);
		Source.GetNetworkIndex(N_X, N_Y, N_Z);
		if (!(((N_Z == (MainNz - 1)) && (IOStat == 0)) || ((N_Z == 0) && (IOStat == (-1))))) {
			IOStat = 1;
			DeadEndCondition = true;
		}
		else DeadEndCondition = false;

		SetPoreProperties(i, PTIndex, X, Y, Z, CoordinationNumber, IOStat, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length);

		AdjacentPores = new int[CoordinationNumber];
		ConnectingThroats = new int[CoordinationNumber];
		Source.GetPoreAndThroatsPointers(i, AdjacentPores, ConnectingThroats);
		SetPoreAndThroatsPointers(i, AdjacentPores, ConnectingThroats);
		delete[] AdjacentPores;
		delete[] ConnectingThroats;
		AdjacentPores = NULL;
		ConnectingThroats = NULL;
			
	}

	SourceThroatNO = Source.GetThroatNO();
	for (i = 0; i < SourceThroatNO; i++) {
		Source.GetThroatProperties(i, PTIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume);
		if (!(((N_Z == (MainNz - 1)) && (IOStat == 0)) || ((N_Z == 0) && (IOStat == (-1))))) {
			IOStat = 1;
			DeadEndCondition = true;
		}
		else DeadEndCondition = false;
		
		SetThroatProperties(i, PTIndex ,Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume, DeadEndCondition);
	}
}

void PoreNetwork::RemoveDeadEnds(void) {
	register unsigned int i;

	for (i = 0; i < PoreNO; i++) {
		if (pores[i].GetDeadEnds()) {

		}
	}
}