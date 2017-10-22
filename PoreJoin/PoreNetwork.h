#ifndef PORENETWORK_H
#define PORENETWORK_H

#include "MIfstream.h"
//#include "ElementList.h"
#include "NetworkElement.h"
//#include "Globals.h"
#include "Pore.h"
#include "Throat.h"





class PoreNetwork {
private:
	Pore *pores;
	Throat *throats;
	unsigned int PoreNO, ThroatNO;
	FloatType Dx, Dy, Dz;				//Dimensions of the porous media
	unsigned int *PorePointer, *ThroatPointer;		
	unsigned int NetworkIndex_X, NetworkIndex_Y, NetworkIndex_Z;

public:
	void ReadStatoilFormat(char *, char *);
	PoreNetwork();
	~PoreNetwork();
	//void SetNeighbours(PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *, PoreNetwork *);
	void SetNetworkIndex(unsigned int, unsigned int, unsigned int);
	void GetNetworkIndex(unsigned int&, unsigned int&, unsigned int&);
	FloatType GetXDim(void);
	FloatType GetYDim(void);
	FloatType GetZDim(void);
	void UpdateMyPoresLocation(FloatType, FloatType, FloatType);
	unsigned int GetPoreNO(void);
	unsigned int GetThroatNO(void);
	void UpdateElementIndex(unsigned int, unsigned int);
	void CopyFromOthers(void);
	void GetPoreProperties(unsigned int, unsigned int&, FloatType &, FloatType &, FloatType &, unsigned int &, int &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &);
	void SetPoreProperties(unsigned int, unsigned int, FloatType, FloatType, FloatType, unsigned int, int, FloatType, FloatType, FloatType, FloatType, FloatType, bool, unsigned int);
	void SetPoreAndThroatsPointers(unsigned int, int *, int *);
	void GetPoreAndThroatsPointers(unsigned int, int *, int *);
	void GetThroatProperties(unsigned int, unsigned int&, int &, int &, int &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &, FloatType &);
	void SetThroatProperties(unsigned int, unsigned int, int, int, int, FloatType, FloatType, FloatType, FloatType, FloatType, FloatType);
	void RemoveDeadEnds(void);
	void GetAllThroatsLengthAndRadius(unsigned int &, FloatType *, FloatType *);
	void MakeNewConnections(void);
	void WriteStatoilFormat(void);
	void GetAllCoNOs(unsigned int &, FloatType *);
};
#endif