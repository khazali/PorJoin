#include <iostream>
#include "Globals.h"
#include "PoreNetwork.h"

int __cdecl main(void) {
	char FName[MAX_PATH_LENGTH];
	
	/*
	std::cout<<"Enter the input file path and name:\n";
	std::cin.getline(FName, MAX_PATH_LENGTH);
	*/
	strcpy(FName, "Data\\indata.dat");

	ReadInput(FName);
	UpdatePoresLocation();	
	GeneralNetwork.CopyFromOthers();
	UpdateIndexes();
	GeneralNetwork.RemoveDeadEnds();
	CalculateStatistics();
	GeneralNetwork.MakeNewConnections();
	GeneralNetwork.WriteStatoilFormat(ResultPath);	
	NormalFinish();

	return 0;
}