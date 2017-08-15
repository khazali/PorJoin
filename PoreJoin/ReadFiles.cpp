#include <iostream>
#include "MIfstream.h"
#include "Globals.h"
#include "dirent.h"
#include "PoreNetwork.h"

void ReadInput(char *InfileName) {
	MIfstream MainInput;
	char str[MAX_STRING_LENGTH];
	unsigned int i, j, k;
	DIR *dir;
	struct dirent *ent;
	
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
				if(!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
				if ((dir = opendir(str)) != NULL) {
					while ((ent = readdir(dir)) != NULL) {
						if ((*(ent->d_name)) != '.') {
							printf("%s\n", ent->d_name);
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