#include <iostream>

#include "dirent.h"
//#include "Globals.h"
#include "PoreNetwork.h"
//#include "MIfstream.h"




void ReadInput(char *InfileName) {
	MIfstream MainInput;
	char str[MAX_STRING_LENGTH], Fname[MAX_STRING_LENGTH];
	register unsigned int i, j, k, n;
	DIR *dir;
	struct dirent *ent;
	unsigned int sLen;
	PoreNetwork *X_Before, *X_After, *Y_Before, *Y_After, *Z_Before, *Z_After;
	FloatType XDim, YDim, ZDim;
	
	MainInput.open(InfileName, std::fstream::in);
	if (!MainInput.is_open()) TerM("Can not open first throat input file!");

	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNx = atoi(str);
	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNy = atoi(str);
	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNz = atoi(str);

	TotalNetworks = MainNx*MainNy*MainNz;
	StatMatrix = new FloatType **[TotalNetworks];
	for (i = 0; i < TotalNetworks; ++i) {
		StatMatrix[i] = new FloatType *[TotalNetworks];
		for (j = 0; j < TotalNetworks; j++) {
			StatMatrix[i][j] = new FloatType[8];
			for (k = 0; k < 8; k++) StatMatrix[i][j][k] = 0;
		}
	}

	Networks = new PoreNetwork[TotalNetworks];
	DXs = new unsigned int[MainNx];
	DYs = new unsigned int[MainNy];
	DZs = new unsigned int[MainNz];
	SumDXs = new unsigned int[MainNx + 1];
	SumDYs = new unsigned int[MainNy + 1];
	SumDZs = new unsigned int[MainNz + 1];
	SumPoreNO = new unsigned int[TotalNetworks + 1];
	SumThroatNO = new unsigned int[TotalNetworks + 1];

	SumPoreNO[0] = 0;
	SumThroatNO[0] = 0;
	for (k = 0; k < MainNz; k++) {
		for (j = 0; j < MainNy; j++) {
			for (i = 0; i < MainNx; i++) {
				*str = '\0';
				MainInput.getline(str, MAX_STRING_LENGTH, '\n');
				if ((*str) == '\0') TerM("Incorrect main file format!");
				if (str[strlen(str) - 1] != '\\') {
					str[strlen(str)] = '\\';
					str[strlen(str) + 1] = '\0';
				}
				if ((dir = opendir(str)) != NULL) {
					while ((ent = readdir(dir)) != NULL) {
						MaxThroatNO = 0;
						if ((*(ent->d_name)) != '.') {
							sLen = (unsigned int)strlen(ent->d_name) - 10;
							for (n = 0; n < sLen; n++) Fname[n] = ent->d_name[i];
							Fname[n] = '\0';
							Networks[k*(MainNy*MainNx) + j*MainNx + i].ReadStatoilFormat(str, Fname);
							
							if (i == 0) X_Before = NULL;
							else X_Before = &Networks[k*(MainNy*MainNx) + j*MainNx + i - 1];
							if (i == (MainNx - 1)) X_After = NULL;
							else X_After = &Networks[k*(MainNy*MainNx) + j*MainNx + i + 1];
							if (j == 0) Y_Before = NULL;
							else Y_Before = &Networks[k*(MainNy*MainNx) + (j - 1)*MainNx + i];
							if (j == (MainNy - 1)) Y_After = NULL;
							else Y_After = &Networks[k*(MainNy*MainNx) + (j + 1)*MainNx + i];
							if (k == 0) Z_Before = NULL;
							else Z_Before = &Networks[(k - 1)*(MainNy*MainNx) + j*MainNx + i];
							if (k == (MainNz - 1)) Z_After = NULL;
							else Z_After = &Networks[(k + 1)*(MainNy*MainNx) + j*MainNx + i];

							Networks[k*(MainNy*MainNx) + j*MainNx + i].SetNeighbours(X_Before, X_After, Y_Before, Y_After, Z_Before, Z_After);
							Networks[k*(MainNy*MainNx) + j*MainNx + i].SetNetworkIndex(i, j, k);

							SumPoreNO[k*(MainNy*MainNx) + j*MainNx + i + 1] = SumPoreNO[k*(MainNy*MainNx) + j*MainNx + i] + Networks[k*(MainNy*MainNx) + j*MainNx + i].GetPoreNO();
							SumThroatNO[k*(MainNy*MainNx) + j*MainNx + i + 1] = SumThroatNO[k*(MainNy*MainNx) + j*MainNx + i] + Networks[k*(MainNy*MainNx) + j*MainNx + i].GetThroatNO();

							if (Networks[k*(MainNy*MainNx) + j*MainNx + i].GetThroatNO() > MaxThroatNO) MaxThroatNO = Networks[k*(MainNy*MainNx) + j*MainNx + i].GetThroatNO();

							break;
						}
					}
					closedir(dir);
				}
				else TerM("Incorrect path in the main file!");
			}
		}
	}
	MainInput.close();



	for (k = 0; k < MainNz; k++) {
		for (j = 0; j < MainNy; j++) {
			YDim = Networks[k*(MainNy*MainNx) + j*MainNx].GetYDim();
			ZDim = Networks[k*(MainNy*MainNx) + j*MainNx].GetZDim();
			for (i = 1; i < MainNx; i++) {
				if ((YDim != Networks[k*(MainNy*MainNx) + j*MainNx + i].GetYDim()) || (ZDim != Networks[k*(MainNy*MainNx) + j*MainNx + i].GetZDim())) {
					TerM("Incompatible Dimensions in the main file!");
				}
			}
		}
	}

	for (k = 0; k < MainNz; k++) {
		for (i = 0; i < MainNx; i++) {
			XDim = Networks[k*(MainNy*MainNx) + i].GetXDim();
			ZDim = Networks[k*(MainNy*MainNx) + i].GetZDim();
			for (j = 1; j < MainNy; j++) {
				if ((XDim != Networks[k*(MainNy*MainNx) + j*MainNx + i].GetXDim()) || (ZDim != Networks[k*(MainNy*MainNx) + j*MainNx + i].GetZDim())) {
					TerM("Incompatible Dimensions in the main file!");
				}
			}
		}
	}

	for (j = 0; j < MainNy; j++) {
		for (i = 0; i < MainNx; i++) {
			XDim = Networks[j*MainNx + i].GetXDim();
			YDim = Networks[j*MainNx + i].GetYDim();
			for (k = 1; k < MainNz; k++) {
				if ((XDim != Networks[k*(MainNy*MainNx) + j*MainNx + i].GetXDim()) || (YDim != Networks[k*(MainNy*MainNx) + j*MainNx + i].GetYDim())) {
					TerM("Incompatible Dimensions in the main file!");
				}
			}
		}
	}

	SumDXs[0] = 0;
	SumDYs[0] = 0;
	SumDZs[0] = 0;

	for (i = 0; i < MainNx; i++) {
		DXs[i] = Networks[i].GetXDim();
		SumDXs[i + 1] = SumDXs[i] + DXs[i];
	}
	for (j = 0; j < MainNy; j++) {
		DYs[j] = Networks[j*MainNx].GetYDim();
		SumDYs[j + 1] = SumDYs[j] + DYs[j];
	}
	for (k = 0; k < MainNz; k++) {
		DZs[k] = Networks[k*(MainNy*MainNx)].GetZDim();
		SumDZs[k + 1] = SumDZs[k] + DZs[k];
	}
}