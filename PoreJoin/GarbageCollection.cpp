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
	delete[] DXs;
	delete[] DYs;
	delete[] DZs;
	delete[] SumDXs;
	delete[] SumDYs;
	delete[] SumDZs;
	delete[] SumPoreNO;
	delete[] SumThroatNO;
}