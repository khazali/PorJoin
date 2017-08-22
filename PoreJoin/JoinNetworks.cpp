#include "Globals.h"
#include "PoreNetwork.h"

void UpdatePoresLocation(void) {
	register unsigned int i, j, k;
	
	for (k = 0; k < MainNz; k++) {
		for (j = 0; j < MainNy; j++) {
			for (i = 0; i < MainNx; i++) {
				Networks[k*(MainNy*MainNx) + j*MainNx + i].UpdatePoresLocation(SumDXs[i], SumDYs[j], SumDZs[k]);
			}
		}
	}
}