#include "Globals.h"
#include "PoreNetwork.h"
#include <cstdlib>
#include <cstdio>
#include <math.h>


void UpdatePoresLocation(void) {
	register unsigned int i, j, k;
	
	for (k = 0; k < MainNz; k++) {
		for (j = 0; j < MainNy; j++) {
			for (i = 0; i < MainNx; i++) {
				Networks[k*(MainNy*MainNx) + j*MainNx + i].UpdateMyPoresLocation(SumDXs[i], SumDYs[j], SumDZs[k]);
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
	FloatType *Lengths1, *Lengths2, *Radius1, *Radius2, *CoNO1, *CoNO2;
	unsigned int LengthNO1, LengthNO2, NOt;
	FloatType SD, Ave, sq1, sq2, sum1, sum2, sqt, sumt;
	FloatType SDR, AveR, sq1R, sq2R, sum1R, sum2R, sqtR, sumtR;
	FloatType SDC, AveC, sq1C, sq2C, sum1C, sum2C, sqtC, sumtC;
	FloatType MinR1, MinR2, MaxR1, MaxR2, MinL1, MinL2, MaxL1, MaxL2;
	FloatType MinC1, MinC2, MaxC1, MaxC2;
	unsigned int CLengthNO1, CLengthNO2, CNOt;

	Lengths1 = new FloatType[MaxThroatNO];
	Lengths2 = new FloatType[MaxThroatNO];
	Radius1 = new FloatType[MaxThroatNO];
	Radius2 = new FloatType[MaxThroatNO];
	CoNO1 = new FloatType[MaxPoreNO];
	CoNO2 = new FloatType[MaxPoreNO];


	sumt = 0;
	sqt = 0;
	NOt = 0;
	sumtR = 0;
	sqtR = 0;
	sumtC = 0;
	sqtC = 0;
	CNOt = 0;
	for (i = 0; i < TotalNetworks; i++) {
		Networks[i].GetAllThroatsLengthAndRadius(LengthNO1, Lengths1, Radius1);
		Networks[i].GetAllCoNOs(CLengthNO1, CoNO1);
		sq1 = 0;
		sum1 = 0;
		sq1R = 0;
		sum1R = 0;		
		for (j = 0; j < LengthNO1; j++) {
			sq1 += Lengths1[j] * Lengths1[j];
			sum1 += Lengths1[j];
			sq1R += Radius1[j] * Radius1[j];
			sum1R += Radius1[j];

			if ((!j) || (MinR1 > Radius1[j])) MinR1 = Radius1[j];
			if ((!j) || (MaxR1 < Radius1[j])) MaxR1 = Radius1[j];
			if ((!j) || (MinL1 > Lengths1[j])) MinL1 = Lengths1[j];
			if ((!j) || (MaxL1 < Lengths1[j])) MaxL1 = Lengths1[j];
		}
		sqt += sq1;
		sumt += sum1;
		sqtR += sq1R;
		sumtR += sum1R;
		NOt += LengthNO1;

		sq1C = 0;
		sum1C = 0;
		for (j = 0; j < CLengthNO1; j++) {
			sq1C += CoNO1[j] * CoNO1[j];
			sum1C += CoNO1[j];

			if ((!j) || (MinC1 > CoNO1[j])) MinC1 = CoNO1[j];
			if ((!j) || (MaxC1 < CoNO1[j])) MaxC1 = CoNO1[j];
		}
		sqtC += sq1C;
		sumtC += sum1C;
		CNOt += CLengthNO1;

		if ((!i) || (MinRadius > MinR1)) MinRadius = MinR1;
		if ((!i) || (MaxRadius < MaxR1)) MaxRadius = MaxR1;
		if ((!i) || (MinLength > MinL1)) MinLength = MinL1;
		if ((!i) || (MaxLength < MaxL1)) MaxLength = MaxL1;
		if ((!i) || (CoNOMin > MinC1)) CoNOMin = MinC1;
		if ((!i) || (CoNOMax < MaxC1)) CoNOMax = MaxC1;

		if ((i%MainNx) != 0) {
			Networks[i - 1].GetAllThroatsLengthAndRadius(LengthNO2, Lengths2, Radius2);
			Networks[i - 1].GetAllCoNOs(CLengthNO2, CoNO2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if ((!j) || (MinR2 > Radius2[j])) MinR2 = Radius2[j];
				if ((!j) || (MaxR2 < Radius2[j])) MaxR2 = Radius2[j];
				if ((!j) || (MinL2 > Lengths2[j])) MinL2 = Lengths2[j];
				if ((!j) || (MaxL2 < Lengths2[j])) MaxL2 = Lengths2[j];
				
			}
			sq2C = 0;
			sum2C = 0;
			for (j = 0; j < CLengthNO2; j++) {
				sq2C += CoNO2[j] * CoNO2[j];
				sum2C += CoNO2[j];

				if ((!j) || (MinC2 > CoNO2[j])) MinC2 = CoNO2[j];
				if ((!j) || (MaxC2 < CoNO2[j])) MaxC2 = CoNO2[j];
			}
			if ((!i) || (MinRadius > MinR2)) MinRadius = MinR2;
			if ((!i) || (MaxRadius < MaxR2)) MaxRadius = MaxR2;
			if ((!i) || (MinLength > MinL2)) MinLength = MinL2;
			if ((!i) || (MaxLength < MaxL2)) MaxLength = MaxL2;
			if ((!i) || (CoNOMin > MinC2)) CoNOMin = MinC2;
			if ((!i) || (CoNOMax < MaxC2)) CoNOMax = MaxC2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR= sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			AveC = (sum1C + sum2C) / (CLengthNO1 + CLengthNO2);
			SDC = sqrt((sq1C + sq2C) / (CLengthNO1 + CLengthNO2) - AveC*AveC);
	
			StatMatrix[i][i - 1][0] = Ave;
			StatMatrix[i][i - 1][1] = SD;
			StatMatrix[i][i - 1][2] = AveR;
			StatMatrix[i][i - 1][3] = SDR;
			StatMatrix[i][i - 1][4] = AveC;
			StatMatrix[i][i - 1][5] = SDC;
			StatMatrix[i][i - 1][6] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i - 1][7] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i - 1][8] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i - 1][9] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
			StatMatrix[i][i - 1][10] = (MinC1 < MinC2) ? MinC1 : MinC2;
			StatMatrix[i][i - 1][11] = (MaxC1 > MaxC2) ? MaxC1 : MaxC2;
			StatMatrix[i][i - 1][12] = CalculateIntegral(Ave, SD, StatMatrix[i][i - 1][6], StatMatrix[i][i - 1][7]);
			StatMatrix[i][i - 1][13] = CalculateIntegral(AveC, SDC, StatMatrix[i][i - 1][10], StatMatrix[i][i - 1][11]);

		}
		if ((i%MainNx) != (MainNx - 1)) {
			Networks[i + 1].GetAllThroatsLengthAndRadius(LengthNO2, Lengths2, Radius2);
			Networks[i + 1].GetAllCoNOs(CLengthNO2, CoNO2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if ((!j) || (MinR2 > Radius2[j])) MinR2 = Radius2[j];
				if ((!j) || (MaxR2 < Radius2[j])) MaxR2 = Radius2[j];
				if ((!j) || (MinL2 > Lengths2[j])) MinL2 = Lengths2[j];
				if ((!j) || (MaxL2 < Lengths2[j])) MaxL2 = Lengths2[j];
			}
			sq2C = 0;
			sum2C = 0;
			for (j = 0; j < CLengthNO2; j++) {
				sq2C += CoNO2[j] * CoNO2[j];
				sum2C += CoNO2[j];

				if ((!j) || (MinC2 > CoNO2[j])) MinC2 = CoNO2[j];
				if ((!j) || (MaxC2 < CoNO2[j])) MaxC2 = CoNO2[j];
			}
			if ((!i) || (MinRadius > MinR2)) MinRadius = MinR2;
			if ((!i) || (MaxRadius < MaxR2)) MaxRadius = MaxR2;
			if ((!i) || (MinLength > MinL2)) MinLength = MinL2;
			if ((!i) || (MaxLength < MaxL2)) MaxLength = MaxL2;
			if ((!i) || (CoNOMin > MinC2)) CoNOMin = MinC2;
			if ((!i) || (CoNOMax < MaxC2)) CoNOMax = MaxC2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			AveC = (sum1C + sum2C) / (CLengthNO1 + CLengthNO2);
			SDC = sqrt((sq1C + sq2C) / (CLengthNO1 + CLengthNO2) - AveC*AveC);

			StatMatrix[i][i + 1][0] = Ave;
			StatMatrix[i][i + 1][1] = SD;
			StatMatrix[i][i + 1][2] = AveR;
			StatMatrix[i][i + 1][3] = SDR;
			StatMatrix[i][i + 1][4] = AveC;
			StatMatrix[i][i + 1][5] = SDC;
			StatMatrix[i][i + 1][6] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i + 1][7] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i + 1][8] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i + 1][9] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
			StatMatrix[i][i + 1][10] = (MinC1 < MinC2) ? MinC1 : MinC2;
			StatMatrix[i][i + 1][11] = (MaxC1 > MaxC2) ? MaxC1 : MaxC2;
			StatMatrix[i][i + 1][12] = CalculateIntegral(Ave, SD, StatMatrix[i][i + 1][6], StatMatrix[i][i + 1][7]);
			StatMatrix[i][i + 1][13] = CalculateIntegral(AveC, SDC, StatMatrix[i][i + 1][10], StatMatrix[i][i + 1][11]);
		}
		if ((i % (MainNx*MainNy)) >= MainNx) {
			Networks[i - MainNx].GetAllThroatsLengthAndRadius(LengthNO2, Lengths2, Radius2);
			Networks[i - MainNx].GetAllCoNOs(CLengthNO2, CoNO2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if ((!j) || (MinR2 > Radius2[j])) MinR2 = Radius2[j];
				if ((!j) || (MaxR2 < Radius2[j])) MaxR2 = Radius2[j];
				if ((!j) || (MinL2 > Lengths2[j])) MinL2 = Lengths2[j];
				if ((!j) || (MaxL2 < Lengths2[j])) MaxL2 = Lengths2[j];
			}
			sq2C = 0;
			sum2C = 0;
			for (j = 0; j < CLengthNO2; j++) {
				sq2C += CoNO2[j] * CoNO2[j];
				sum2C += CoNO2[j];

				if ((!j) || (MinC2 > CoNO2[j])) MinC2 = CoNO2[j];
				if ((!j) || (MaxC2 < CoNO2[j])) MaxC2 = CoNO2[j];
			}
			if ((!i) || (MinRadius > MinR2)) MinRadius = MinR2;
			if ((!i) || (MaxRadius < MaxR2)) MaxRadius = MaxR2;
			if ((!i) || (MinLength > MinL2)) MinLength = MinL2;
			if ((!i) || (MaxLength < MaxL2)) MaxLength = MaxL2;
			if ((!i) || (CoNOMin > MinC2)) CoNOMin = MinC2;
			if ((!i) || (CoNOMax < MaxC2)) CoNOMax = MaxC2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			AveC = (sum1C + sum2C) / (CLengthNO1 + CLengthNO2);
			SDC = sqrt((sq1C + sq2C) / (CLengthNO1 + CLengthNO2) - AveC*AveC);

			StatMatrix[i][i - MainNx][0] = Ave;
			StatMatrix[i][i - MainNx][1] = SD;
			StatMatrix[i][i - MainNx][2] = AveR;
			StatMatrix[i][i - MainNx][3] = SDR;
			StatMatrix[i][i - MainNx][4] = AveC;
			StatMatrix[i][i - MainNx][5] = SDC;
			StatMatrix[i][i - MainNx][6] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i - MainNx][7] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i - MainNx][8] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i - MainNx][9] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
			StatMatrix[i][i - MainNx][10] = (MinC1 < MinC2) ? MinC1 : MinC2;
			StatMatrix[i][i - MainNx][11] = (MaxC1 > MaxC2) ? MaxC1 : MaxC2;
			StatMatrix[i][i - MainNx][12] = CalculateIntegral(Ave, SD, StatMatrix[i][i - MainNx][6], StatMatrix[i][i - MainNx][7]);
			StatMatrix[i][i - MainNx][13] = CalculateIntegral(AveC, SDC, StatMatrix[i][i - MainNx][10], StatMatrix[i][i - MainNx][11]);
		}
		if ((i % (MainNx*MainNy)) < (MainNx*MainNy - MainNx)) {
			Networks[i + MainNx].GetAllThroatsLengthAndRadius(LengthNO2, Lengths2, Radius2);
			Networks[i + MainNx].GetAllCoNOs(CLengthNO2, CoNO2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if ((!j) || (MinR2 > Radius2[j])) MinR2 = Radius2[j];
				if ((!j) || (MaxR2 < Radius2[j])) MaxR2 = Radius2[j];
				if ((!j) || (MinL2 > Lengths2[j])) MinL2 = Lengths2[j];
				if ((!j) || (MaxL2 < Lengths2[j])) MaxL2 = Lengths2[j];
			}
			sq2C = 0;
			sum2C = 0;
			for (j = 0; j < CLengthNO2; j++) {
				sq2C += CoNO2[j] * CoNO2[j];
				sum2C += CoNO2[j];

				if ((!j) || (MinC2 > CoNO2[j])) MinC2 = CoNO2[j];
				if ((!j) || (MaxC2 < CoNO2[j])) MaxC2 = CoNO2[j];
			}
			if ((!i) || (MinRadius > MinR2)) MinRadius = MinR2;
			if ((!i) || (MaxRadius < MaxR2)) MaxRadius = MaxR2;
			if ((!i) || (MinLength > MinL2)) MinLength = MinL2;
			if ((!i) || (MaxLength < MaxL2)) MaxLength = MaxL2;
			if ((!i) || (CoNOMin > MinC2)) CoNOMin = MinC2;
			if ((!i) || (CoNOMax < MaxC2)) CoNOMax = MaxC2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			AveC = (sum1C + sum2C) / (CLengthNO1 + CLengthNO2);
			SDC = sqrt((sq1C + sq2C) / (CLengthNO1 + CLengthNO2) - AveC*AveC);

			StatMatrix[i][i + MainNx][0] = Ave;
			StatMatrix[i][i + MainNx][1] = SD;
			StatMatrix[i][i + MainNx][2] = AveR;
			StatMatrix[i][i + MainNx][3] = SDR;
			StatMatrix[i][i + MainNx][4] = AveC;
			StatMatrix[i][i + MainNx][5] = SDC;
			StatMatrix[i][i + MainNx][6] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i + MainNx][7] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i + MainNx][8] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i + MainNx][9] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
			StatMatrix[i][i + MainNx][10] = (MinC1 < MinC2) ? MinC1 : MinC2;
			StatMatrix[i][i + MainNx][11] = (MaxC1 > MaxC2) ? MaxC1 : MaxC2;
			StatMatrix[i][i + MainNx][12] = CalculateIntegral(Ave, SD, StatMatrix[i][i + MainNx][6], StatMatrix[i][i + MainNx][7]);
			StatMatrix[i][i + MainNx][13] = CalculateIntegral(AveC, SDC, StatMatrix[i][i + MainNx][10], StatMatrix[i][i + MainNx][11]);
		}
		if (((int)(i)-(int)(MainNx*MainNy)) >= 0) {
			Networks[i - MainNx*MainNy].GetAllThroatsLengthAndRadius(LengthNO2, Lengths2, Radius2);
			Networks[i - MainNx*MainNy].GetAllCoNOs(CLengthNO2, CoNO2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if ((!j) || (MinR2 > Radius2[j])) MinR2 = Radius2[j];
				if ((!j) || (MaxR2 < Radius2[j])) MaxR2 = Radius2[j];
				if ((!j) || (MinL2 > Lengths2[j])) MinL2 = Lengths2[j];
				if ((!j) || (MaxL2 < Lengths2[j])) MaxL2 = Lengths2[j];
			}
			sq2C = 0;
			sum2C = 0;
			for (j = 0; j < CLengthNO2; j++) {
				sq2C += CoNO2[j] * CoNO2[j];
				sum2C += CoNO2[j];

				if ((!j) || (MinC2 > CoNO2[j])) MinC2 = CoNO2[j];
				if ((!j) || (MaxC2 < CoNO2[j])) MaxC2 = CoNO2[j];
			}
			if ((!i) || (MinRadius > MinR2)) MinRadius = MinR2;
			if ((!i) || (MaxRadius < MaxR2)) MaxRadius = MaxR2;
			if ((!i) || (MinLength > MinL2)) MinLength = MinL2;
			if ((!i) || (MaxLength < MaxL2)) MaxLength = MaxL2;
			if ((!i) || (CoNOMin > MinC2)) CoNOMin = MinC2;
			if ((!i) || (CoNOMax < MaxC2)) CoNOMax = MaxC2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			AveC = (sum1C + sum2C) / (CLengthNO1 + CLengthNO2);
			SDC = sqrt((sq1C + sq2C) / (CLengthNO1 + CLengthNO2) - AveC*AveC);

			StatMatrix[i][i - MainNx*MainNy][0] = Ave;
			StatMatrix[i][i - MainNx*MainNy][1] = SD;
			StatMatrix[i][i - MainNx*MainNy][2] = AveR;
			StatMatrix[i][i - MainNx*MainNy][3] = SDR;
			StatMatrix[i][i - MainNx*MainNy][4] = AveC;
			StatMatrix[i][i - MainNx*MainNy][5] = SDC;
			StatMatrix[i][i - MainNx*MainNy][6] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i - MainNx*MainNy][7] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i - MainNx*MainNy][8] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i - MainNx*MainNy][9] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
			StatMatrix[i][i - MainNx*MainNy][10] = (MinC1 < MinC2) ? MinC1 : MinC2;
			StatMatrix[i][i - MainNx*MainNy][11] = (MaxC1 > MaxC2) ? MaxC1 : MaxC2;
			StatMatrix[i][i - MainNx*MainNy][12] = CalculateIntegral(Ave, SD, StatMatrix[i][i - MainNx*MainNy][6], StatMatrix[i][i - MainNx*MainNy][7]);
			StatMatrix[i][i - MainNx*MainNy][13] = CalculateIntegral(AveC, SDC, StatMatrix[i][i - MainNx*MainNy][10], StatMatrix[i][i - MainNx*MainNy][11]);
		}
		if ((i + MainNx*MainNy) < (MainNx*MainNy*MainNz)) {
			Networks[i + MainNx*MainNy].GetAllThroatsLengthAndRadius(LengthNO2, Lengths2, Radius2);
			Networks[i + MainNx*MainNy].GetAllCoNOs(CLengthNO2, CoNO2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if ((!j) || (MinR2 > Radius2[j])) MinR2 = Radius2[j];
				if ((!j) || (MaxR2 < Radius2[j])) MaxR2 = Radius2[j];
				if ((!j) || (MinL2 > Lengths2[j])) MinL2 = Lengths2[j];
				if ((!j) || (MaxL2 < Lengths2[j])) MaxL2 = Lengths2[j];
			}
			sq2C = 0;
			sum2C = 0;
			for (j = 0; j < CLengthNO2; j++) {
				sq2C += CoNO2[j] * CoNO2[j];
				sum2C += CoNO2[j];

				if ((!j) || (MinC2 > CoNO2[j])) MinC2 = CoNO2[j];
				if ((!j) || (MaxC2 < CoNO2[j])) MaxC2 = CoNO2[j];
			}
			if ((!i) || (MinRadius > MinR2)) MinRadius = MinR2;
			if ((!i) || (MaxRadius < MaxR2)) MaxRadius = MaxR2;
			if ((!i) || (MinLength > MinL2)) MinLength = MinL2;
			if ((!i) || (MaxLength < MaxL2)) MaxLength = MaxL2;
			if ((!i) || (CoNOMin > MinC2)) CoNOMin = MinC2;
			if ((!i) || (CoNOMax < MaxC2)) CoNOMax = MaxC2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			AveC = (sum1C + sum2C) / (CLengthNO1 + CLengthNO2);
			SDC = sqrt((sq1C + sq2C) / (CLengthNO1 + CLengthNO2) - AveC*AveC);

			StatMatrix[i][i + MainNx*MainNy][0] = Ave;
			StatMatrix[i][i + MainNx*MainNy][1] = SD;
			StatMatrix[i][i + MainNx*MainNy][2] = AveR;
			StatMatrix[i][i + MainNx*MainNy][3] = SDR;
			StatMatrix[i][i + MainNx*MainNy][4] = AveC;
			StatMatrix[i][i + MainNx*MainNy][5] = SDC;
			StatMatrix[i][i + MainNx*MainNy][6] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i + MainNx*MainNy][7] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i + MainNx*MainNy][8] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i + MainNx*MainNy][9] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
			StatMatrix[i][i + MainNx*MainNy][10] = (MinC1 < MinC2) ? MinC1 : MinC2;
			StatMatrix[i][i + MainNx*MainNy][11] = (MaxC1 > MaxC2) ? MaxC1 : MaxC2;
			StatMatrix[i][i + MainNx*MainNy][12] = CalculateIntegral(Ave, SD, StatMatrix[i][i + MainNx*MainNy][6], StatMatrix[i][i + MainNx*MainNy][7]);
			StatMatrix[i][i + MainNx*MainNy][13] = CalculateIntegral(AveC, SDC, StatMatrix[i][i + MainNx*MainNy][10], StatMatrix[i][i + MainNx*MainNy][11]);
		}		
	}
	LengthTotalAve = sumt / NOt;
	LengthTotalSD = sqrt(sqt / NOt - LengthTotalAve*LengthTotalAve);
	RadiusTotalAve = sumtR / NOt;
	RadiusTotalSD = sqrt(sqtR / NOt - RadiusTotalAve*RadiusTotalAve);
	CoNOAve = sumtC / CNOt;
	CoNOSD = sqrt(sqtC / CNOt - CoNOAve*CoNOAve);
	LIntegral = CalculateIntegral(LengthTotalAve, LengthTotalSD, MinLength, MaxLength);
	CIntegral = CalculateIntegral(CoNOAve, CoNOSD, CoNOMin, CoNOMax);
	
	delete[] Lengths1;
	delete[] Lengths2;
	delete[] Radius1;
	delete[] Radius2;
	delete[] CoNO1;
	delete[] CoNO2;
}

FloatType NormalSelect(FloatType Length, FloatType Average, FloatType StandardDeviation, FloatType Min, FloatType Max, FloatType cProb) {
	if ((Length < Min) || (Length > Max)) return 0;	
	else return cProb*exp(-(Length - Average)*(Length - Average) / (2 * StandardDeviation*StandardDeviation));	
}

FloatType NormRand(FloatType Average, FloatType StandardDeviation, FloatType Min, FloatType Max) {
	FloatType U1, U2, W, mult, NRand;
	static FloatType X1, X2;
	static bool call = false;

	do {
		if (call) {
			call = !call;
			NRand = Average + StandardDeviation * (double)X2;
		}
		else {
			do {
				U1 = -1 + ((double)rand() / RAND_MAX) * 2;
				U2 = -1 + ((double)rand() / RAND_MAX) * 2;
				W = pow(U1, 2) + pow(U2, 2);
			} while (W >= 1 || W == 0);

			mult = sqrt((-2 * log(W)) / W);
			X1 = U1 * mult;
			X2 = U2 * mult;

			call = !call;

			NRand = Average + StandardDeviation * (double)X1;
		}
	} while ((NRand<Min) || (NRand>Max));	

	return NRand;
}

FloatType CalculateIntegral(FloatType Average, FloatType StandardDeviation, FloatType Min, FloatType Max) {
	FloatType cProb, Integral, a, x, h;
	register unsigned int i;

	h = (Max - Min) / SIMPSON_1_3_INTEGRATION;
	Integral = 0;
	for (i = 0; i < SIMPSON_1_3_INTEGRATION; i++) {
		x = Min + i*h;
		if ((!i) || (i == (SIMPSON_1_3_INTEGRATION - 1))) a = exp(-(x - Average)*(x - Average) / (2 * StandardDeviation*StandardDeviation));
		else if ((i % 2)) a = 4 * exp(-(x - Average)*(x - Average) / (2 * StandardDeviation*StandardDeviation));
		else a = 2 * exp(-(x - Average)*(x - Average) / (2 * StandardDeviation*StandardDeviation));

		Integral += a;
	}
	Integral *= h / 3;

	cProb = ConnectionFraction*(Max - Min) / Integral;
	return cProb;
}
