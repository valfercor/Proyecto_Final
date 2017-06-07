#pragma once

#define BandSpace 4
#define BandGrosor 7

class Bandx
{
public:
	Bandx();
	~Bandx();

	bool esDerecha;
	double gear1x;
	double gear1y;
	double gear2x;

	//void DrawBand(CG::Gdi& gdi, double gear1x, double gear1y, double gear2x, int gearRadio);
	void DrawBand(CG::Gdi& gdi,int gearDiameter,float delta);
};

