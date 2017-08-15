#include <cstdlib>
#include <iostream>
#include "Globals.h"
#include "Pore.h"
#include "Throat.h"


void TerM(char *ErrorMessage) {
	NormalFinish();

	std::cout<<ErrorMessage<<std::endl;
	std::exit(EXIT_FAILURE);
}

void NormalFinish(void) {
	delete[] Networks;
}