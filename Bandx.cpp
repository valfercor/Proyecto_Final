#include "stdafx.h"
#include "Bandx.h"


Bandx::Bandx()
{
	esDerecha = true;
}


Bandx::~Bandx()
{
}

void Bandx::DrawBand(CG::Gdi& gdi, int GearDiameter,float delta)
{


	CG::Pen RedPen(PS_SOLID, BandGrosor, RGB(20, 0, 0));
	gdi.SelectNullBrush();
	gdi.Select(RedPen);

	RECT band;
	band.left = gear2x + (BandSpace + GearDiameter);
	band.right = gear1x - (BandSpace + GearDiameter);
	band.top = gear1y - (BandSpace + GearDiameter);
	band.bottom = gear1y + (BandSpace + GearDiameter);

	gdi.RoundRect(band, GearDiameter * 2, GearDiameter * 2);

	//No happenig
	//CG::Brush GearColor = RGB(153, 153, 153);
	//gdi.Select(GearColor);
	//gdi.SelectNullPen();
	//static double angle = 0.0;
	//static double WidthPie = 45.0;//ancho 
	//if (esDerecha == false) //velocidad
	//	angle += 30.0*delta;
	//else
	//	angle -= 30.0*delta;

	////First Gear
	//gdi.PieCircle(gear1x, gear1y, GearDiameter, angle, WidthPie);
	//gdi.PieCircle(gear1x, gear1y, GearDiameter, angle + 90.0, WidthPie);
	//gdi.PieCircle(gear1x, gear1y, GearDiameter, angle + 180.0, WidthPie);
	//gdi.PieCircle(gear1x, gear1y, GearDiameter, angle + 270.0, WidthPie);
	////Second Gear
	//gdi.PieCircle(gear2x, gear1y, GearDiameter, angle, WidthPie);
	//gdi.PieCircle(gear2x, gear1y, GearDiameter, angle + 90.0, WidthPie);
	//gdi.PieCircle(gear2x, gear1y, GearDiameter, angle + 180.0, WidthPie);
	//gdi.PieCircle(gear2x, gear1y, GearDiameter, angle + 270.0, WidthPie);
}