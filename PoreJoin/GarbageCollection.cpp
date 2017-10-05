#include <cstdlib>
#include <iostream>
#include "Globals.h"
#include "Pore.h"
#include "Throat.h"
#include "PoreNetwork.h"


void TerM(char *ErrorMessage) {
	NormalFinish();

	std::cout<<ErrorMessage<<std::endl;
	std::exit(EXIT_FAILURE);
}

void NormalFinish(void) {
	register unsigned int i, j;

	delete[] Networks;
	delete[] DXs;
	delete[] DYs;
	delete[] DZs;
	delete[] SumDXs;
	delete[] SumDYs;
	delete[] SumDZs;
	delete[] SumPoreNO;
	delete[] SumThroatNO;

	for (i = 0; i < TotalNetworks; ++i) {		
		for (j = 0; j < TotalNetworks; j++) delete[] StatMatrix[i][j];
		delete[] StatMatrix[i];
	}
	delete[] StatMatrix;
}