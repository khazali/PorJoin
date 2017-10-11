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
	FloatType *Lengths1, *Lengths2, *Radius1, *Radius2;
	unsigned int LengthNO1, LengthNO2, NOt;
	FloatType SD, Ave, sq1, sq2, sum1, sum2, sqt, sumt;
	FloatType SDR, AveR, sq1R, sq2R, sum1R, sum2R, sqtR, sumtR;
	FloatType MinR1, MinR2, MaxR1, MaxR2, MinL1, MinL2, MaxL1, MaxL2;

	Lengths1 = new FloatType[MaxThroatNO];
	Lengths2 = new FloatType[MaxThroatNO];
	Radius1 = new FloatType[MaxThroatNO];
	Radius2 = new FloatType[MaxThroatNO];

	sumt = 0;
	sqt = 0;
	NOt = 0;
	sumtR = 0;
	sqtR = 0;
	MinLength = 0;
	MaxLength = 0;
	MinRadius = 0;
	MaxRadius = 0;
	for (i = 0; i < TotalNetworks; i++) {
		Networks[i].GetAllThroatsLength(LengthNO1, Lengths1, Radius1);
		sq1 = 0;
		sum1 = 0;
		sq1R = 0;
		sum1R = 0;

		MinR1 = 0;
		MinL1 = 0;
		MaxR1 = 0;
		MaxL1 = 0;
		for (j = 0; j < LengthNO1; j++) {
			sq1 += Lengths1[j] * Lengths1[j];
			sum1 += Lengths1[j];
			sq1R += Radius1[j] * Radius1[j];
			sum1R += Radius1[j];

			if (MinR1 > Radius1[j]) MinR1 = Radius1[j];
			if (MaxR1 < Radius1[j]) MaxR1 = Radius1[j];
			if (MinL1 > Lengths1[j]) MinL1 = Lengths1[j];
			if (MaxL1 < Lengths1[j]) MaxR1 = Lengths1[j];
		}
		sqt += sq1;
		sumt += sum1;
		sqtR += sq1R;
		sumtR += sum1R;
		NOt += LengthNO1;

		if (MinRadius > MinR1) MinRadius = MinR1;
		if (MaxRadius < MaxR1) MaxRadius = MinR1;
		if (MinLength > MinL1) MinLength = MinL1;
		if (MaxLength < MaxL1) MaxLength = MaxL1;

		if ((i%MainNx) != 0) {
			Networks[i - 1].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			MinR2 = 0;
			MinL2 = 0;
			MaxR2 = 0;
			MaxL2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if (MinR2 > Radius1[j]) MinR2 = Radius2[j];
				if (MaxR2 < Radius1[j]) MaxR2 = Radius2[j];
				if (MinL2 > Lengths1[j]) MinL2 = Lengths2[j];
				if (MaxL2 < Lengths1[j]) MaxR2 = Lengths2[j];
				
			}
			if (MinRadius > MinR2) MinRadius = MinR2;
			if (MaxRadius < MaxR2) MaxRadius = MinR2;
			if (MinLength > MinL2) MinLength = MinL2;
			if (MaxLength < MaxL2) MaxLength = MaxL2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR= sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
	
			StatMatrix[i][i - 1][0] = Ave;
			StatMatrix[i][i - 1][1] = SD;
			StatMatrix[i][i - 1][2] = AveR;
			StatMatrix[i][i - 1][3] = SDR;
			StatMatrix[i][i - 1][4] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i - 1][5] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i - 1][6] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i - 1][7] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
		}
		if ((i%MainNx) != (MainNx - 1)) {
			Networks[i + 1].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			MinR2 = 0;
			MinL2 = 0;
			MaxR2 = 0;
			MaxL2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if (MinR2 > Radius1[j]) MinR2 = Radius2[j];
				if (MaxR2 < Radius1[j]) MaxR2 = Radius2[j];
				if (MinL2 > Lengths1[j]) MinL2 = Lengths2[j];
				if (MaxL2 < Lengths1[j]) MaxR2 = Lengths2[j];
			}
			if (MinRadius > MinR2) MinRadius = MinR2;
			if (MaxRadius < MaxR2) MaxRadius = MinR2;
			if (MinLength > MinL2) MinLength = MinL2;
			if (MaxLength < MaxL2) MaxLength = MaxL2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			StatMatrix[i][i + 1][0] = Ave;
			StatMatrix[i][i + 1][1] = SD;
			StatMatrix[i][i + 1][2] = AveR;
			StatMatrix[i][i + 1][3] = SDR;
			StatMatrix[i][i + 1][4] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i + 1][5] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i + 1][6] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i + 1][7] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
		}
		if ((i % (MainNx*MainNy)) >= MainNx) {
			Networks[i - MainNx].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			MinR2 = 0;
			MinL2 = 0;
			MaxR2 = 0;
			MaxL2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if (MinR2 > Radius1[j]) MinR2 = Radius2[j];
				if (MaxR2 < Radius1[j]) MaxR2 = Radius2[j];
				if (MinL2 > Lengths1[j]) MinL2 = Lengths2[j];
				if (MaxL2 < Lengths1[j]) MaxR2 = Lengths2[j];
			}
			if (MinRadius > MinR2) MinRadius = MinR2;
			if (MaxRadius < MaxR2) MaxRadius = MinR2;
			if (MinLength > MinL2) MinLength = MinL2;
			if (MaxLength < MaxL2) MaxLength = MaxL2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			StatMatrix[i][i - MainNx][0] = Ave;
			StatMatrix[i][i - MainNx][1] = SD;
			StatMatrix[i][i - MainNx][2] = AveR;
			StatMatrix[i][i - MainNx][3] = SDR;
			StatMatrix[i][i - MainNx][4] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i - MainNx][5] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i - MainNx][6] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i - MainNx][7] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
		}
		if ((i % (MainNx*MainNy)) < (MainNx*MainNy - MainNx)) {
			Networks[i + MainNx].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			MinR2 = 0;
			MinL2 = 0;
			MaxR2 = 0;
			MaxL2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if (MinR2 > Radius1[j]) MinR2 = Radius2[j];
				if (MaxR2 < Radius1[j]) MaxR2 = Radius2[j];
				if (MinL2 > Lengths1[j]) MinL2 = Lengths2[j];
				if (MaxL2 < Lengths1[j]) MaxR2 = Lengths2[j];
			}
			if (MinRadius > MinR2) MinRadius = MinR2;
			if (MaxRadius < MaxR2) MaxRadius = MinR2;
			if (MinLength > MinL2) MinLength = MinL2;
			if (MaxLength < MaxL2) MaxLength = MaxL2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			StatMatrix[i][i + MainNx][0] = Ave;
			StatMatrix[i][i + MainNx][1] = SD;
			StatMatrix[i][i + MainNx][2] = AveR;
			StatMatrix[i][i + MainNx][3] = SDR;
			StatMatrix[i][i + MainNx][4] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i + MainNx][5] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i + MainNx][6] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i + MainNx][7] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
		}
		if (((int)(i)-(int)(MainNx*MainNy)) >= 0) {
			Networks[i - MainNx*MainNy].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			MinR2 = 0;
			MinL2 = 0;
			MaxR2 = 0;
			MaxL2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if (MinR2 > Radius1[j]) MinR2 = Radius2[j];
				if (MaxR2 < Radius1[j]) MaxR2 = Radius2[j];
				if (MinL2 > Lengths1[j]) MinL2 = Lengths2[j];
				if (MaxL2 < Lengths1[j]) MaxR2 = Lengths2[j];
			}
			if (MinRadius > MinR2) MinRadius = MinR2;
			if (MaxRadius < MaxR2) MaxRadius = MinR2;
			if (MinLength > MinL2) MinLength = MinL2;
			if (MaxLength < MaxL2) MaxLength = MaxL2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			StatMatrix[i][i - MainNx*MainNy][0] = Ave;
			StatMatrix[i][i - MainNx*MainNy][1] = SD;
			StatMatrix[i][i - MainNx*MainNy][2] = AveR;
			StatMatrix[i][i - MainNx*MainNy][3] = SDR;
			StatMatrix[i][i - MainNx*MainNy][4] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i - MainNx*MainNy][5] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i - MainNx*MainNy][6] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i - MainNx*MainNy][7] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
		}
		if (i + MainNx*MainNy < MainNx*MainNy*MainNz) {
			Networks[i + MainNx*MainNy].GetAllThroatsLength(LengthNO2, Lengths2, Radius2);
			sq2 = 0;
			sum2 = 0;
			sq2R = 0;
			sum2R = 0;

			MinR2 = 0;
			MinL2 = 0;
			MaxR2 = 0;
			MaxL2 = 0;
			for (j = 0; j < LengthNO2; j++) {
				sq2 += Lengths2[j] * Lengths2[j];
				sum2 += Lengths2[j];
				sq2R += Radius2[j] * Radius2[j];
				sum2R += Radius2[j];

				if (MinR2 > Radius1[j]) MinR2 = Radius2[j];
				if (MaxR2 < Radius1[j]) MaxR2 = Radius2[j];
				if (MinL2 > Lengths1[j]) MinL2 = Lengths2[j];
				if (MaxL2 < Lengths1[j]) MaxR2 = Lengths2[j];
			}
			if (MinRadius > MinR2) MinRadius = MinR2;
			if (MaxRadius < MaxR2) MaxRadius = MinR2;
			if (MinLength > MinL2) MinLength = MinL2;
			if (MaxLength < MaxL2) MaxLength = MaxL2;

			Ave = (sum1 + sum2) / (LengthNO1 + LengthNO2);
			SD = sqrt((sq1 + sq2) / (LengthNO1 + LengthNO2) - Ave*Ave);
			AveR = (sum1R + sum2R) / (LengthNO1 + LengthNO2);
			SDR = sqrt((sq1R + sq2R) / (LengthNO1 + LengthNO2) - AveR*AveR);
			StatMatrix[i][i + MainNx*MainNy][0] = Ave;
			StatMatrix[i][i + MainNx*MainNy][1] = SD;
			StatMatrix[i][i + MainNx*MainNy][2] = AveR;
			StatMatrix[i][i + MainNx*MainNy][3] = SDR;
			StatMatrix[i][i + MainNx*MainNy][4] = (MinL1 < MinL2) ? MinL1 : MinL2;
			StatMatrix[i][i + MainNx*MainNy][5] = (MaxL1 > MaxL2) ? MaxL1 : MaxL2;
			StatMatrix[i][i + MainNx*MainNy][6] = (MinR1 < MinR2) ? MinR1 : MinR2;
			StatMatrix[i][i + MainNx*MainNy][7] = (MaxR1 > MaxR2) ? MaxR1 : MaxR2;
		}		
	}
	LengthTotalAve = sumt / NOt;
	LengthTotalSD = sqrt(sqt / NOt - LengthTotalAve*LengthTotalAve);
	RadiusTotalAve = sumtR / NOt;
	RadiusTotalSD = sqrt(sqtR / NOt - RadiusTotalAve*RadiusTotalAve);
	
	delete[] Lengths1;
	delete[] Lengths2;
	delete[] Radius1;
	delete[] Radius2;
}

bool NormalSelect(FloatType Length, FloatType Average, FloatType StandardDeviation, FloatType Min, FloatType Max) {
	FloatType cProb, Integral, a, x, h, SelectionProbability;
	register unsigned int i;

	if ((Length < Min) || (Length > Max)) return false;

	h = (Max - Min) / SIMPSON_1_3_INTEGRATION;
	Integral = 0;
	for (i = 0; i < SIMPSON_1_3_INTEGRATION; i++) {
		x = Min + i*h;
		if ((!i) || (i == (SIMPSON_1_3_INTEGRATION - 1))) a = exp(-(x - Average)*(x - Average) / (2 * x*x));
		else if ((i % 2)) a = 4 * exp(-(x - Average)*(x - Average) / (2 * x*x));
		else a = 2 * exp(-(x - Average)*(x - Average) / (2 * x*x));

		Integral += a;
	}
	Integral *= h / 3;

	cProb = CONNECTION_FRACTION*(Max - Min) / Integral;
	SelectionProbability = cProb*exp(-(Length - Average)*(Length - Average) / (2 * Length*Length));

	return ((((FloatType)rand()) / RAND_MAX) < SelectionProbability);
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