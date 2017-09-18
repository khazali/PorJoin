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

void UpdateIndexes(void) {
	register unsigned int i, j, k;

	for (k = 0; k < MainNz; k++) {
		for (j = 0; j < MainNy; j++) {
			for (i = 0; i < MainNx; i++) {
				Networks[k*(MainNy*MainNx) + j*MainNx + i].UpdateElementIndex(SumPoreNO[k*(MainNy*MainNx) + j*MainNx + i], SumThroatNO[k*(MainNy*MainNx) + j*MainNx + i]);
			}
		}
	}
}

void CalculateStatistics(void) {
	register unsigned int i, j;
	FloatType *Lengths1, *Lengths2, *Radius1, *Radius2;
	unsigned int LengthNO1, LengthNO2, NOt;
	FloatType SD, Ave, sq1, sq2, sum1, sum2, sqt, sumt;
	FloatType SDR, AveR, sq1R, sq2R, sum1R, sum2R, sqtR, sumtR;

	Lengths1 = new FloatType[MaxThroatNO];
	Lengths2 = new FloatType[MaxThroatNO];
	Radius1 = new FloatType[MaxThroatNO];
	Radius2 = new FloatType[MaxThroatNO];

	sumt = 0;
	sqt = 0;
	NOt = 0;
	sumtR = 0;
	sqtR = 0;
	for (i = 0; i < TotalNetworks; i++) {
		Networks[i].GetAllThroatsLength(LengthNO1, Lengths1, Radius1);
		sq1 = 0;
		sum1 = 0;
		for (j = 0; j < LengthNO1; j++) {
			sq1 += Lengths1[j] * Lengths1[j];
			sum1 += Lengths1[j];
		}
		sqt += sq1;
		sumt += sum1;
		NOt += LengthNO1;
		if ((i%MainNx) != 0) {
			Networks[i - 1].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
			}
			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			StatMatrix[i][i - 1][0] = Ave;
			StatMatrix[i][i - 1][1] = SD;
		}
		if ((i%MainNx) != (MainNx - 1)) {
			Networks[i + 1].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
			}
			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			StatMatrix[i][i + 1][0] = Ave;
			StatMatrix[i][i + 1][1] = SD;
		}
		if ((i % (MainNx*MainNy)) >= MainNx) {
			Networks[i - MainNx].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
			}
			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			StatMatrix[i][i - MainNx][0] = Ave;
			StatMatrix[i][i - MainNx][1] = SD;
		}
		if ((i % (MainNx*MainNy)) < (MainNx*MainNy - MainNx)) {
			Networks[i + MainNx].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
			}
			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			StatMatrix[i][i + MainNx][0] = Ave;
			StatMatrix[i][i + MainNx][1] = SD;
		}
		if (((int)(i)-(int)(MainNx*MainNy)) >= 0) {
			Networks[i - MainNx*MainNy].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
			}
			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			StatMatrix[i][i - MainNx*MainNy][0] = Ave;
			StatMatrix[i][i - MainNx*MainNy][1] = SD;
		}
		if (i + MainNx*MainNy < MainNx*MainNy*MainNz) {
			Networks[i + MainNx*MainNy].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
			}
			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			StatMatrix[i][i + MainNx*MainNy][0] = Ave;
			StatMatrix[i][i + MainNx*MainNy][1] = SD;
		}		
	}
	LengthTotalAve = sumt / NOt;
	LengthTotalSD = sqrt(sqt / NOt - LengthTotalAve*LengthTotalAve);
	
	delete[] Lengths1;
	delete[] Lengths2;
	delete[] Radius1;
	delete[] Radius2;
}

void MergeNetworks(void) {
	GeneralNetwork.CopyFromOthers();
	GeneralNetwork.RemoveDeadEnds();
}