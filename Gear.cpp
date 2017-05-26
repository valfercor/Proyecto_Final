#include "stdafx.h"
#include "Gear.h"


Gear::Gear()
{

}


Gear::~Gear()
{
}

void Gear::DrawGear(CG::Gdi& gdi, double CenterX, double CenterY)
{

	CG::Brush Brush(RGB(150, 100, 0));
	CG::Pen GearPen(PS_SOLID, 2, RGB(200, 150, 0));
	gdi.Select(Brush);
	gdi.Select(GearPen);

	gdi.Circle(CenterX, CenterY, GearRadio);
}