#include "stdafx.h"
#include "Bandx.h"


Bandx::Bandx()
{
}


Bandx::~Bandx()
{
}

void Bandx::DrawBand(CG::Gdi& gdi, double gear1x, double gear1y, double gear2x, double gear2y, int GearRadio)
{

	CG::Brush RedBrush(RGB(230, 10, 10));
	CG::Pen RedPen(PS_SOLID, 2, RGB(200, 10, 10));

	RECT band;
	band.left = gear2x + (BandSpace +GearRadio);
	band.right = gear1x - (BandSpace + GearRadio);
	band.top = gear1y - (BandSpace + GearRadio);
	band.bottom = gear1y + (BandSpace + GearRadio);

	gdi.Rectangle(band);
}