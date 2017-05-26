#include "stdafx.h"
#include "Box.h"


Box::Box()
{

}


Box::~Box()
{
}

void Box::DrawBox(CG::Gdi& gdi, double left, double bottom, int type, bool orange)
{

	CG::Brush OrangeBrush(RGB(230, 10, 200));
	CG::Pen OrangePen(PS_SOLID, 2, RGB(200, 10, 200));
	CG::Brush RedBrush(RGB(230, 10, 10));
	CG::Pen RedPen(PS_SOLID, 2, RGB(200, 10, 10));

	if (orange == true)
	{
		gdi.Select(OrangeBrush);
		gdi.Select(OrangePen);
	}
	else
	{
		gdi.Select(RedBrush);
		gdi.Select(RedPen);
	}
	RECT box;
	box.bottom = bottom;
	box.left = left;

	if (type == 1)//Square
	{
		box.top = bottom + BoxSize;
		box.top = left + BoxSize;

	}
	else if (type == 2)//horizontal
	{
		box.top = bottom + (BoxSize / 2);
		box.top = left + BoxSize;
	}
	else
	{
		box.top = bottom + BoxSize;
		box.top = left + (BoxSize / 2);
	}

	gdi.Rectangle(box);
}
