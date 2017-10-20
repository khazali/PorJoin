#include "PoreNetwork.h"
#include "MIfstream.h"
#include <fstream>
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
		throats[i].ReadLink1(ThroatData1);
		throats[i].ReadLink2(ThroatData2, pores);
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

void PoreNetwork::UpdateMyPoresLocation(FloatType X_Origin, FloatType Y_Origin, FloatType Z_Origin) {
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

void PoreNetwork::SetPoreProperties(unsigned int PIndex, unsigned int PoreIndex, FloatType X, FloatType Y, FloatType Z, unsigned int CoordinationNumber, int IOStat, FloatType Volume, FloatType InscribedRadius, FloatType ShapeFactor, FloatType ClayVolume, FloatType Length, bool DeadEndCondition, unsigned int PrimaryIndex) {
	pores[PIndex].SetProperties(PoreIndex, X, Y, Z, CoordinationNumber, IOStat, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length, DeadEndCondition, PrimaryIndex);
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

void PoreNetwork::GetThroatPropertiesWithDeadEnd(unsigned int TIndex, unsigned int &ThroatIndex, int &Pore1Index, int &Pore2Index, int &IOStat, FloatType &InscribedRadius, FloatType &ShapeFactor, FloatType &TotalLength, FloatType &Length, FloatType &Volume, FloatType &ClayVolume, bool &DeadEndCondition) {
	throats[TIndex].GetPropertiesWithDeadEnd(ThroatIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume, DeadEndCondition);
}

void PoreNetwork::SetThroatProperties(unsigned int TIndex, unsigned int ThroatIndex, int Pore1Index, int Pore2Index, int IOStat, FloatType InscribedRadius, FloatType ShapeFactor, FloatType TotalLength, FloatType Length, FloatType Volume, FloatType ClayVolume, bool DeadEndCondition) {
	throats[TIndex].SetProperties(ThroatIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume, DeadEndCondition);
}

void PoreNetwork::CopyFromOthers(void) {
	register unsigned int i, Ix, Iy, Iz, j;
	FloatType X, Y, Z, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length, TotalLength;
	unsigned int Coordination_Number, SourcePoreNO, SourceThroatNO, PTIndex, N_X, N_Y, N_Z, PrimaryIndex;
	int IOStat, Pore1Index, Pore2Index;
	int *AdjacentPores, *ConnectingThroats;
	bool DeadEndCondition;
	PoreNetwork *Source;
	unsigned int BasePoreNO, BaseThroatNO;

	PoreNO = SumPoreNO[TotalNetworks];
	ThroatNO = SumThroatNO[TotalNetworks];
	Dx = SumDXs[MainNx];
	Dy = SumDXs[MainNy];
	Dz = SumDXs[MainNz];	
	throats = new Throat[MAX_THROATS_COEFFICIENT*ThroatNO];
	pores = new Pore[PoreNO];
	
	for (Iz = 0; Iz < MainNz; Iz++) {
		for (Iy = 0; Iy < MainNy; Iy++) {
			for (Ix = 0; Ix < MainNx; Ix++) {
				Source = &Networks[Iz*(MainNy*MainNx) + Iy*MainNx + Ix];
				BasePoreNO = SumPoreNO[Iz*(MainNy*MainNx) + Iy*MainNx + Ix];
				BaseThroatNO = SumThroatNO[Iz*(MainNy*MainNx) + Iy*MainNx + Ix];

				SourcePoreNO = Source->GetPoreNO();
				for (i = 0; i < SourcePoreNO; i++) {
					Source->GetPoreProperties(i, PTIndex, X, Y, Z, Coordination_Number, IOStat, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length);
					Source->GetNetworkIndex(N_X, N_Y, N_Z);
					if (((IOStat == 0) && (N_Z != (MainNz - 1))) || ((IOStat == (-1)) && (N_Z != 0))) {
					//if (!(((N_Z == (MainNz - 1)) && (IOStat == 0)) || ((N_Z == 0) && (IOStat == (-1))))) {
						IOStat = 1;
						DeadEndCondition = true;
					}
					else DeadEndCondition = false;
					PrimaryIndex = Iz*(MainNy*MainNx) + Iy*MainNx + Ix;

					SetPoreProperties(i + BasePoreNO, PTIndex, X, Y, Z, Coordination_Number, IOStat, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length, DeadEndCondition, PrimaryIndex);

					AdjacentPores = new int[Coordination_Number];
					ConnectingThroats = new int[Coordination_Number];
					Source->GetPoreAndThroatsPointers(i, AdjacentPores, ConnectingThroats);
					for (j = 0; j < Coordination_Number; j++) {
						if (AdjacentPores[j] > 0) AdjacentPores[j] += BasePoreNO;
						ConnectingThroats[j] += BaseThroatNO;
					}
					SetPoreAndThroatsPointers(i + BasePoreNO, AdjacentPores, ConnectingThroats);
					delete[] AdjacentPores;
					delete[] ConnectingThroats;
					AdjacentPores = NULL;
					ConnectingThroats = NULL;

				}

				SourceThroatNO = Source->GetThroatNO();
				for (i = 0; i < SourceThroatNO; i++) {
					Source->GetThroatProperties(i, PTIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume);
					if (((IOStat == 0) && (N_Z != (MainNz - 1))) || ((IOStat == (-1)) && (N_Z != 0))) {
					//if (!(((N_Z == (MainNz - 1)) && (IOStat == 0)) || ((N_Z == 0) && (IOStat == (-1))))) {
						IOStat = 1;
						DeadEndCondition = true;
					}
					else DeadEndCondition = false;
					if (Pore1Index > 0) Pore1Index += BasePoreNO;
					if (Pore2Index > 0) Pore2Index += BasePoreNO;
					SetThroatProperties(i + BaseThroatNO, PTIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume, DeadEndCondition);
				}
			}
		}
	}	
}

void PoreNetwork::RemoveDeadEnds(void) {
	register unsigned int i, j, k;
	register unsigned int p, r, d, q, C2UMSize, u, TempVar;
	unsigned int CoNumber, Nulls;
	int P2Pore, P2Throat;
	unsigned int PTIndex;
	FloatType Volume, InscribedRadius, ShapeFactor, ClayVolume, Length, TotalLength;
	int IOStat, Pore1Index, Pore2Index;	
	bool DeadEndCondition;
	unsigned int DeletedThroats = 0;
	unsigned int *DeadPool = new unsigned int[2 * ThroatNO];
	unsigned int *ReverseIndex = new unsigned int[ThroatNO];

	for (i = 0; i < ThroatNO; i++) ReverseIndex[i] = 0;

	for (i = 0; i < PoreNO; i++) {
		if (pores[i].GetDeadEnds()) {
			CoNumber = pores[i].GetCoordinationNumber();
			Nulls = 0;
			for (j = 0; j < (CoNumber - Nulls); j++) {
				pores[i].GetNumberedConnectingPoreAndThroats(j - Nulls, P2Pore, P2Throat);
				if (P2Pore < 1) {
					DeadPool[DeletedThroats] = P2Throat;
					DeletedThroats++;
					pores[i].DelBranch(j - Nulls);
					Nulls++;
				}
			}
			//pores[i].SetCoordinationNumber(CoNumber - Nulls);
		}
	}
	///////////////////////////////////////
	

	u = DeletedThroats;
	k = 0;
	while (u) {
		u >>= 1;
		k++;
	}
	u = 1;
	u <<= (k - 1);

	if (u == DeletedThroats) C2UMSize = DeletedThroats;
	else C2UMSize = u << 1;

	i = C2UMSize >> 1;
	for (p = i; p >= 1; p >>= 1) {
		r = 0;
		d = p;
		for (q = i; q >= p; q >>= 1) {
			for (k = 0; k < (C2UMSize - d); k++) {
				if ((k & p) != r) continue;
				if ((k < DeletedThroats) && ((k + d) < DeletedThroats) && (DeadPool[k] > DeadPool[k + d])) {
					TempVar = DeadPool[k];
					DeadPool[k] = DeadPool[k + d];
					DeadPool[k + d] = TempVar;
				}
			}
			d = q - p;
			r = p;
		}
	}

	j = 0;
	for (i = 0; i < (ThroatNO - DeletedThroats); i++) {
		ReverseIndex[i] = i - j;
		if (j) {
			throats[i].GetPropertiesWithDeadEnd(PTIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume, DeadEndCondition);
			throats[i - j].SetProperties(i - j, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume, DeadEndCondition);			
		}
		if (((i + 1) == DeadPool[j]) && (j < DeletedThroats)) {
			j++;
		}
	}
	////////////////////////////////////////
	ThroatNO -= DeletedThroats;

	for (i = 0; i < PoreNO; i++) {
		pores[i].UpdateConnectingThroatIndexes(ReverseIndex);
	}
		
	delete[] DeadPool;
	delete[] ReverseIndex;
}

void PoreNetwork::GetAllThroatsLength(unsigned int &NumberOfThroats , FloatType *Lengths, FloatType *IR) {
	register unsigned int i;

	NumberOfThroats = ThroatNO;
	for (i = 0; i < ThroatNO; i++) {
		Lengths[i] = throats[i].GetTotalLength();
		IR[i] = throats[i].GetInscribedRadius();
	}
}

void PoreNetwork::MakeNewConnections(void) {
	register unsigned int i, j;
	FloatType Distance, LAve, LSD, RAve, RSD, LMin, LMax, RMin, RMax;
	unsigned int iPrimaryIndex, jPrimaryIndex;
	FloatType TRadius, TVolume, TLength;
	//int TPore1Index, TPore2Index;
	unsigned int AddedPores = 0;
	unsigned int CompletePercent;

	for (i = 0; i < (PoreNO - 1); i++) {
		
		if ((!i) || (CompletePercent != (unsigned int)((i + 1.0)*100.0 / PoreNO))) {
			CompletePercent = (unsigned int)((i + 1.0)*100.0 / PoreNO);
			std::cout << "\r" << CompletePercent << "\tPercent Completed!";
		}
		
		for (j = (i + 1); j < PoreNO; j++) {
			iPrimaryIndex = pores[i].GetPrimaryIndex();
			jPrimaryIndex = pores[j].GetPrimaryIndex();
			if (iPrimaryIndex == jPrimaryIndex) continue;
			Distance = sqrt((pores[i].GetX() - pores[j].GetX())*(pores[i].GetX() - pores[j].GetX()) + (pores[i].GetY() - pores[j].GetY())*(pores[i].GetY() - pores[j].GetY()) + (pores[i].GetZ() - pores[j].GetZ())*(pores[i].GetZ() - pores[j].GetZ()));
			if (USE_GLOBAL_DISTRIBUTION) {
				LAve = LengthTotalAve;
				LSD = LengthTotalSD;
				RAve = RadiusTotalAve;
				RSD = RadiusTotalSD;
				LMin = MinLength;
				LMax = MaxLength;
				RMin = MinRadius;
				RMax = MaxRadius;
			}
			else {
				LAve = StatMatrix[iPrimaryIndex][jPrimaryIndex][0];
				LSD = StatMatrix[iPrimaryIndex][jPrimaryIndex][1];
				RAve = StatMatrix[iPrimaryIndex][jPrimaryIndex][2];
				RSD = StatMatrix[iPrimaryIndex][jPrimaryIndex][3];
				LMin = StatMatrix[iPrimaryIndex][jPrimaryIndex][4];
				LMax = StatMatrix[iPrimaryIndex][jPrimaryIndex][5];
				RMin = StatMatrix[iPrimaryIndex][jPrimaryIndex][6];
				RMax = StatMatrix[iPrimaryIndex][jPrimaryIndex][7];
			}
			if (NormalSelect(Distance, LAve, LSD, LMin, LMax)) {
				TRadius = NormRand(RAve, RSD, RMin, RMax);
				//add throats between i and j
				//throats[k].SetProperties(PTIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume, DeadEndCondition);
				TLength = Distance - pores[i].GetLength() - pores[j].GetLength();
				TVolume = PI*TRadius*TRadius*TLength;
				throats[ThroatNO].SetProperties(ThroatNO, i + 1, j + 1, 1, TRadius, 1.0 / (4.0*PI), Distance, TLength, TVolume, 0, false);
				ThroatNO++;
				pores[i].AddThroat(ThroatNO, j + 1);
				pores[j].AddThroat(ThroatNO, i + 1);
				AddedPores++;
			}
		}
	}

	std::cout << '\r' << AddedPores << "\t\tPores connected!\n\n";
}

void PoreNetwork::WriteStatoilFormat(char *FilePath) {
	std::ofstream ThroatData1, ThroatData2, PoreData1, PoreData2;
	char ThroatData1File[MAX_PATH_LENGTH], ThroatData2File[MAX_PATH_LENGTH], PoreData1File[MAX_PATH_LENGTH], PoreData2File[MAX_PATH_LENGTH];
	unsigned int sLen;

	unsigned int i;
	FloatType X, Y, Z, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length, TotalLength, P1Length, P2Length;
	unsigned int CoordinationNumber, PTIndex;
	int IOStat, Pore1Index, Pore2Index;
	char Prefix[MAX_STRING_LENGTH] = "Result";

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

	ThroatData1.open(ThroatData1File, std::fstream::out);
	if (!ThroatData1.is_open()) TerM("Can not open first throat input file!");
	ThroatData2.open(ThroatData2File, std::fstream::out);
	if (!ThroatData2.is_open()) TerM("Can not open second throat input file!");
	PoreData1.open(PoreData1File, std::fstream::out);
	if (!PoreData1.is_open()) TerM("Can not open first pore input file!");
	PoreData2.open(PoreData2File, std::fstream::out);
	if (!PoreData2.is_open()) TerM("Can not open second pore input file!");

	ThroatData1 << ThroatNO << std::endl;
	for (i = 0; i < ThroatNO; i++) {
		throats[i].GetProperties(PTIndex, Pore1Index, Pore2Index, IOStat, InscribedRadius, ShapeFactor, TotalLength, Length, Volume, ClayVolume);
		ThroatData1 << i + 1 << '\t' << Pore1Index << '\t' << Pore2Index << '\t' << InscribedRadius << '\t' << ShapeFactor << '\t' << TotalLength << std::endl;
		if (Pore1Index > 0) P1Length = pores[Pore1Index - 1].GetLength();
		else P1Length = 0;
		if (Pore2Index > 0) P2Length = pores[Pore2Index - 1].GetLength();
		else P2Length = 0;
		ThroatData2 << i + 1 << '\t' << Pore1Index << '\t' << Pore2Index << '\t' << P1Length << '\t' << P2Length << '\t' << Length << '\t' << Volume << '\t' << ClayVolume << std::endl;
		
	}
	ThroatData1.close();
	ThroatData2.close();

	PoreData1 << PoreNO << '\t' << Dx << '\t' << Dy << '\t' << Dz << std::endl;
	for (i = 0; i < PoreNO; i++) {
		pores[i].GetProperties(PTIndex, X, Y, Z, CoordinationNumber, IOStat, Volume, InscribedRadius, ShapeFactor, ClayVolume, Length);
		PoreData1 << i + 1 << '\t' << X << '\t' << Y << '\t' << Z << '\t' << CoordinationNumber << '\t';
		pores[i].WriteNeighbours(PoreData1);
		PoreData1 << std::endl;
		PoreData2 << i + 1 << '\t' << Volume << '\t' << InscribedRadius << '\t' << ShapeFactor << '\t' << ClayVolume << std::endl;
	}
	PoreData1.close();
	PoreData2.close();
}