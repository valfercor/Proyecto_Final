#pragma once
#define BoxSize 60
#define BoxSpeed 250

class Box
{
public:
	Box();
	~Box();
	double left;
	double bottom;
	int BandNumber;
	bool PrimerMovimiento;
	int type; 
	bool IsOrange; 
	bool Caida;
	void DrawBox(CG::Gdi& gdi, float delta, bool esDerecha);
	
};

