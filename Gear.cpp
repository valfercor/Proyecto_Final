#include "stdafx.h"
#include "Gear.h"


Gear::Gear()
{
	WhichGear = 0;
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

	//gdi.Circle(CenterX, CenterY, GearDiameter);
	//if (WhichGear == 0)
	//	Icon.Load(hInstance, IDI_GEAR);
	//else
//		Icon.Load(hInstance, IDI_GEAR1);
//	gdi.DrawIcon(CenterX - GearDiameter, CenterY - GearDiameter, Icon);


}