#include <iostream>
#include "MIfstream.h"
#include "Globals.h"

void ReadInput(char *InfileName) {
	MIfstream MainInput;
	char str[MAX_STRING_LENGTH];

	MainInput.open(InfileName, std::fstream::in);
	if (!MainInput.is_open()) TerM("Can not open first throat input file!");

	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNx = atoi(str);
	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNy = atoi(str);
	if (!MainInput.ReadWord(str)) TerM("Incorrect main file format!");
	MainNz = atoi(str);

	MainInput.close();
}