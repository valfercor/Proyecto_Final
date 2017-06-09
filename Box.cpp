#include "stdafx.h"
#include "Box.h"


Box::Box()
{
	left =  (2 * BoxSize + 50) / 2.0;
	bottom=3.08 * BoxSize - 19;
	PrimerMovimiento = true;
	BandNumber = 0;
	IsOrange = true;
	type = 0;
	Caida = false;
	
}


Box::~Box()
{
}

void Box::DrawBox(CG::Gdi& gdi, float delta, bool esDerecha)
{
	//Update position
	if (PrimerMovimiento == true)
	{

		if (BandNumber == 0)
		{
			left = (int)(left + BoxSpeed*delta + 0.5);
		}
		if (BandNumber == 1)
		{
			bottom = (int)(bottom + BoxSpeed*delta + 0.5);
		}

	}

	if(PrimerMovimiento==false && BandNumber==1)
	{
		if (esDerecha == true)
			left = (int)(left + BoxSpeed*delta + 0.5);
		else
			left = (int)(left - (BoxSpeed*delta + 0.5));
	}

	if (Caida == true)
	{
		bottom = (int)(bottom + BoxSpeed*delta + 0.5);
	}



	if (Caida == false && BandNumber >= 2)
	{
		if (esDerecha == true)
			left = (int)(left + BoxSpeed*delta + 0.5);
		else
			left = (int)(left - (BoxSpeed*delta + 0.5));
	}

	


	//____Draw
	CG::Brush OrangeBrush(RGB(255, 117, 020));
	CG::Brush RedBrush(RGB(179, 040, 033));
	gdi.SelectNullPen();


	if (IsOrange == true)
	{
		gdi.Select(OrangeBrush);
	}
	else
	{
		gdi.Select(RedBrush);

	}
	RECT box;
	box.bottom = bottom;
	box.left = left;

	if (type == 0)//Square
	{
		box.top = bottom - BoxSize;
		box.right = left + BoxSize;

	}
	else if (type == 1)//horizontal
	{
		box.top = bottom - (BoxSize / 2);
		box.right = left + BoxSize;
	}
	else
	{
		box.top = bottom - BoxSize;
		box.right = left + (BoxSize / 2);
	}

	gdi.Rectangle(box);
}

