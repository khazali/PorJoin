#ifndef NETWORKELEMENT_H
#define NETWORKELEMENT_H

#include "Globals.h"

class NetworkElement {
protected:
	FloatType Z;				//Height coordinate
	unsigned int Index;
	bool IsConnectedToOutlet, IsConnectedToInlet;
	bool IsVisited;	
	bool IsEnabled;
	FloatType ClayVolume;
	FloatType Volume;
	FloatType Length;
	int IOStat;					//Inlet=-1, Outlet=0, Normal=1;
	FloatType ShapeFactor;
	FloatType InscribedRadius;

public:
	void SetIndex(unsigned int);
	NetworkElement(void);
	void SetIsConnectedToOutlet(FluidType, bool);
	bool GetIsConnectedToOutlet(FluidType);
	void SetIsConnectedToInlet(bool);
	bool GetIsConnectedToInlet(void);
	void SetIsVisited(bool);
	bool GetIsVisited(void);
	FloatType GetZ(void);
	unsigned int GetIndex(void);
	bool GetIsEnabled(void);
	void SetIsEnabled(bool);
	FloatType GetLength(void);
};
#endif