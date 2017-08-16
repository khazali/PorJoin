#include <iostream>
#include "MIfstream.h"
#include "Globals.h"
#include "dirent.h"
#include "PoreNetwork.h"

void ReadInput(char *InfileName) {
	MIfstream MainInput;
	char str[MAX_STRING_LENGTH], Fname[MAX_STRING_LENGTH];
	register unsigned int i, j, k, n;
	DIR *dir;
	struct dirent *ent;
	unsigned int sLen;
	
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
							break;
						}
					}
					closedir(dir);
				}
				else TerM("Incorrect path in the main file!");
				/////////////////Read Finish





			}
		}
	}



	MainInput.close();
}