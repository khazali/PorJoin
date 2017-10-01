#include <iostream>
#include "Globals.h"
#include "PoreNetwork.h"

int __cdecl main(void) {
	char FName[MAX_PATH_LENGTH];
	
	std::cout<<"Enter the input file path and name:\n";
	std::cin.getline(FName, MAX_PATH_LENGTH);

	ReadInput(FName);
	GeneralNetwork.CopyFromOthers();
	GeneralNetwork.RemoveDeadEnds();
	CalculateStatistics();
	GeneralNetwork.MakeNewConnections();
	GeneralNetwork.WriteStatoilFormat(ResultPath);	
	NormalFinish();

	return 0;
}