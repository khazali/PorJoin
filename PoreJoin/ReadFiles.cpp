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
	
	MainInput.open(InfileName, std::fstream::in);
	if (!MainInput.is_open()) TerM("Can not open first throat input file!");

	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNx = atoi(str);
	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNy = atoi(str);
	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNz = atoi(str);

	TotalNetworks = MainNx*MainNy*MainNz + 1;
	Networks = new PoreNetwork[TotalNetworks];

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
}