#include "stdafx.h"  //________________________________________ Sort_It.cpp
#include "Sort_It.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR cmdLine, int cmdShow) {
	Sort_It app;
	app.CreateMainWindow(L"Sort_It", cmdShow, IDI_Sort_It, NULL, (HBRUSH)::GetStockObject(NULL_BRUSH), hInstance);
	return app.MessageLoop(IDC_Sort_It);

}

void Sort_It::Window_Open(Win::Event& e)
{
	//________Background
	BitmapBG.CreateFromResource(this->hInstance, IDB_BACKGROUND);
	
	FirstTime = true;
	this->Show(SW_SHOWMAXIMIZED);//para hacer grande la pantalla
}

bool Sort_It::RenderScene(CG::Gdi& gdi)
{
	static DWORD prevTime = timeGetTime();
	const DWORD currentTime = timeGetTime();
	const float delta = (currentTime - prevTime) / 1000.0f;
	static double tiempo = 0;
	tiempo += delta;

	float levelHeight = (height - (BoxSize + 2 * DEFAULTV)) / 4;
	float typeWidth = width / 3;
	float SpaceHorizontal = BoxSize + DEFAULTH + BandSpace + (GearDiameter / 2);
	float SpaceVertical = DEFAULTV + BandSpace + (GearDiameter / 2);

	//____________________________________________ Paint Window Background
	CG::Brush brush(RGB(10, 10, 55));
	RECT rect = { 0, 0, width, height };
	gdi.FillRect(rect, brush);
	gdi.DrawBitmap(BitmapBG, 0, 0);


	//____________________________________________ Paint Bands
	DefineBandPosition(typeWidth, levelHeight, SpaceVertical, SpaceHorizontal);
	PaintBands(gdi, delta, typeWidth, levelHeight, SpaceVertical, SpaceHorizontal);
	double BottomLimit = height - (BoxSize / 2);

	//gdi.Line(0, height - (BoxSize/2), width, height - (BoxSize/2));

	
	if (FirstTime == true)
	{
		MoveBox(gdi, delta, 0);
		if (Box[0].bottom == BottomLimit)
			FirstTime = false;
	}
	else
	{
		MoveBox(gdi, delta, 0);
		MoveBox(gdi, delta, 1);
	}
	//MoveBox(gdi, delta, 0);
	//if (Box[0].bottom >= BottomLimit)
	//	ResetBox(0);

	//MoveBox(gdi, delta, 1);
	//if (Box[1].bottom >= BottomLimit)
	//	ResetBox(1);

		

	
	

	prevTime = timeGetTime();
	return true; // return false to stop
}
void Sort_It::ResetBox(int NumberOfBoxes)
{
	Box[NumberOfBoxes].left = (2 * BoxSize + 50) / 2.0;
	Box[NumberOfBoxes].bottom = 3.08 * BoxSize - 19;
	Box[NumberOfBoxes].PrimerMovimiento = true;
	Box[NumberOfBoxes].BandNumber = 0;
	Box[NumberOfBoxes].IsOrange = rand() % 2;
	Box[NumberOfBoxes].type = rand() % 3;
	Box[NumberOfBoxes].Caida = false;
}

void Sort_It::MoveBox(CG::Gdi gdi,float delta,int NumberOfBoxes)
{
	int  SPACER = (GearDiameter/2 )+ 2*BandGrosor ;
	int  SPACEL = (GearDiameter / 2) - 2*BandGrosor ;
	int  SPACEBoxR = SPACER + BoxSize;
	int  SPACEBoxL = SPACEL - BoxSize;
	//____________________BOXES
	
	//Band 0
	if (Box[NumberOfBoxes].PrimerMovimiento == true)
	{
		if (Box[NumberOfBoxes].left >= Band[0].gear2x + SPACER && Box[NumberOfBoxes].left <= Band[0].gear2x + SPACEBoxR && Box[NumberOfBoxes].BandNumber == 0)
		{
			Box[NumberOfBoxes].BandNumber++;
		}
		Box[NumberOfBoxes].DrawBox(gdi, delta, false);

	}

	//Collision Banda 1
	if (Box[NumberOfBoxes].bottom >= Band[1].gear1y - SPACER  && Box[NumberOfBoxes].BandNumber == 1)
	{
		Box[NumberOfBoxes].PrimerMovimiento = false;
		Box[NumberOfBoxes].DrawBox(gdi, delta, Band[1].esDerecha);
		//______Limite Izquierdo
		if (Box[NumberOfBoxes].left >= Band[1].gear1x-(GearDiameter/2)-2*BandGrosor-BoxSize-20 && Box[0].left <= Band[1].gear1x - (GearDiameter / 2) - 2 * BandGrosor-BoxSize)
		{
			Box[NumberOfBoxes].BandNumber++;
			Box[NumberOfBoxes].Caida = true;
		}
		
		//______Limite Derecho
		else if (Box[NumberOfBoxes].left >= Band[1].gear2x + SPACER && Box[NumberOfBoxes].left <= Band[1].gear2x + SPACEBoxR)
		{
			Box[NumberOfBoxes].BandNumber=5;
			Box[NumberOfBoxes].Caida = true;
		}
	}
	if(Box[NumberOfBoxes].BandNumber == 1)
		Box[NumberOfBoxes].DrawBox(gdi, delta, Band[1].esDerecha);
		
	//Collision Banda 2
	if (Box[NumberOfBoxes].bottom >= Band[2].gear1y - SPACER  && Box[NumberOfBoxes].BandNumber == 2)
	{
		Box[NumberOfBoxes].Caida = false;
		Box[NumberOfBoxes].DrawBox(gdi, delta, Band[2].esDerecha);
		//______Limite Izquierdo
		if (Box[NumberOfBoxes].left >= Band[2].gear1x - (GearDiameter / 2) - 2 * BandGrosor - BoxSize - 20 && Box[NumberOfBoxes].left <= Band[2].gear1x - (GearDiameter / 2) - 2 * BandGrosor - BoxSize)
		{
			Box[NumberOfBoxes].BandNumber++;
			Box[NumberOfBoxes].Caida = true;
		}

		//______Limite Derecho
		else if (Box[NumberOfBoxes].left >= Band[2].gear2x + SPACER && Box[0].left <= Band[2].gear2x + SPACEBoxR)
		{
			Box[NumberOfBoxes].BandNumber += 2;
			Box[NumberOfBoxes].Caida = true;
		}	
	}

	if(Box[NumberOfBoxes].BandNumber == 2)
		Box[NumberOfBoxes].DrawBox(gdi, delta, Band[2].esDerecha);
	if ((Box[NumberOfBoxes].BandNumber == 3 || Box[NumberOfBoxes].BandNumber == 4) && Box[NumberOfBoxes].Caida == true && Box[NumberOfBoxes].bottom <= Band[3].gear1y)
		Box[NumberOfBoxes].DrawBox(gdi, delta, Band[Box[NumberOfBoxes].BandNumber].esDerecha);

	//Caida derecha a Banda 5
	if (Box[NumberOfBoxes].BandNumber == 5 && Box[NumberOfBoxes].Caida == true)
		Box[NumberOfBoxes].DrawBox(gdi, delta, Band[1].esDerecha);

	//Collision ultimo nivel
	if (Box[NumberOfBoxes].bottom >= Band[3].gear1y - SPACER  && (Box[NumberOfBoxes].BandNumber >=3))
	{
		NumeroCajas++;
		Box[NumberOfBoxes].Caida = false;
		if (Box[NumberOfBoxes].BandNumber == 3)
		{
			//______Limite Izquierdo
				if (Box[NumberOfBoxes].left >= 0 && Box[NumberOfBoxes].left <= Band[3].gear1x - (GearDiameter / 2) - 2 * BandGrosor - BoxSize)
					Box[NumberOfBoxes].Caida = true;
			//______Limite Derecho
				if (Box[NumberOfBoxes].left >= Band[3].gear2x + SPACER && Box[NumberOfBoxes].left <= Band[3].gear2x + SPACEBoxR)
					Box[NumberOfBoxes].Caida = true;
			Box[NumberOfBoxes].DrawBox(gdi, delta, Band[3].esDerecha);
		}

		if (Box[NumberOfBoxes].BandNumber == 4)
		{
			//______Limite Izquierdo
			if (Box[NumberOfBoxes].left >= Band[3].gear2x + SPACER && Box[NumberOfBoxes].left <= Band[4].gear1x - (GearDiameter / 2) - 2 * BandGrosor - BoxSize)
				Box[NumberOfBoxes].Caida = true;
			//______Limite Derecho
			if (Box[NumberOfBoxes].left >= Band[4].gear2x + SPACER && Box[NumberOfBoxes].left <= Band[4].gear2x + SPACEBoxR)
				Box[NumberOfBoxes].Caida = true;
			Box[NumberOfBoxes].DrawBox(gdi, delta, Band[4].esDerecha);
		}

		if (Box[NumberOfBoxes].BandNumber == 5)
		{
			//______Limite Izquierdo
			if (Box[NumberOfBoxes].left >= Band[4].gear2x + SPACER && Box[NumberOfBoxes].left <= Band[5].gear1x - (GearDiameter / 2) - 2 * BandGrosor - BoxSize)
				Box[NumberOfBoxes].Caida = true;
			//______Limite Derecho
			if (Box[NumberOfBoxes].left >= Band[5].gear2x + SPACER && Box[NumberOfBoxes].left <= width)
				Box[NumberOfBoxes].Caida = true;

			Box[NumberOfBoxes].DrawBox(gdi, delta, Band[5].esDerecha);
		}
		
	}
	
}



void Sort_It::Window_LButtonDown(Win::Event& e)
{
	const int x = GET_X_LPARAM(e.lParam);
	const int y = GET_Y_LPARAM(e.lParam);
	
	ChangeDirection(x, y);

}

void Sort_It::ChangeDirection(int x, int y)
{
	for (int i = 1; i <= 5; i++)
	{
		RECT borderBand;
		borderBand.left = Band[i].gear1x + (BandSpace + GearDiameter);
		borderBand.right = Band[i].gear2x + (BandSpace + GearDiameter);
		borderBand.top = Band[i].gear1y - (BandSpace + GearDiameter);
		borderBand.bottom = Band[i].gear1y + (BandSpace + GearDiameter);

		if (x <= borderBand.right && x >= borderBand.left)
			if (y >= borderBand.top&&y <= borderBand.bottom)
			{
				this->Text = L"Band Clicked: ";
				this->Text += Sys::Convert::ToString(i);
				if (Band[i].esDerecha == true)
				{
					Band[i].esDerecha = false;
				}
				else 
				{
					Band[i].esDerecha = true;
				}
			}
	}
}


void Sort_It::PaintBands(CG::Gdi gdi,float delta, float typeWidth, float levelHeight,float SpaceVertical, float SpaceHorizontal)
{
	
	//static double angle = 0.0;
	double WidthPie = 45.0;//ancho 
	static double angle[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	CG::Brush GearColor = RGB(100, 100, 100);
	


	for (int i = 0; i <= 5; i++)
	{
		gdi.Select(GearColor);
		gdi.SelectNullPen();

		if (Band[i].esDerecha == false) //velocidad y direccion
			angle[i] += GearSpeed*delta;
		else
			angle[i] -= GearSpeed* delta;
		//First Gear
		gdi.PieCircle(Band[i].gear1x, Band[i].gear1y, GearDiameter, angle[i], WidthPie);
		gdi.PieCircle(Band[i].gear1x, Band[i].gear1y, GearDiameter, angle[i] + 90.0, WidthPie);
		gdi.PieCircle(Band[i].gear1x, Band[i].gear1y, GearDiameter, angle[i] + 180.0, WidthPie);
		gdi.PieCircle(Band[i].gear1x, Band[i].gear1y, GearDiameter, angle[i] + 270.0, WidthPie);
		//Second Gear
		gdi.PieCircle(Band[i].gear2x, Band[i].gear1y, GearDiameter, angle[i], WidthPie);
		gdi.PieCircle(Band[i].gear2x, Band[i].gear1y, GearDiameter, angle[i] + 90.0, WidthPie);
		gdi.PieCircle(Band[i].gear2x, Band[i].gear1y, GearDiameter, angle[i] + 180.0, WidthPie);
		gdi.PieCircle(Band[i].gear2x, Band[i].gear1y, GearDiameter, angle[i] + 270.0, WidthPie);

		Band[i].DrawBand(gdi, GearDiameter, delta);
	}


}

void Sort_It::DefineBandPosition(float typeWidth, float levelHeight, float SpaceVertical, float SpaceHorizontal)
{
	//_________Band 0 _______Level 0
	Band[0].gear1x = (2 * BoxSize + 50) / 2.0;
	Band[0].gear1y = 3.08 * BoxSize;
	Band[0].gear2x = width / 2;	



	//________Band 2 _______Level 2
	Band[2].gear1x = 0.5*typeWidth + SpaceHorizontal;
	Band[2].gear1y = 3 * levelHeight - SpaceVertical;
	Band[2].gear2x = 1.5*typeWidth - SpaceHorizontal;


	//_________Band 1 _______Level 1
	Band[1].gear1x = typeWidth + SpaceHorizontal;
	Band[1].gear1y =( Band[2].gear1y+ Band[0].gear1y) / 2.0 ;//2 * levelHeight - SpaceVertical;
	Band[1].gear2x = 2 * typeWidth + 1.5*SpaceHorizontal;



	//_________Band 3 _______Level 3
	Band[3].gear1x = SpaceHorizontal;
	Band[3].gear1y = 4 * levelHeight - SpaceVertical;
	Band[3].gear2x = typeWidth - SpaceHorizontal;
	//_________Band 4 _______Level 3
	Band[4].gear1x = typeWidth + SpaceHorizontal;
	Band[4].gear1y = 4 * levelHeight - SpaceVertical;
	Band[4].gear2x = 2 * typeWidth - SpaceHorizontal;
	//_________Band 5 _______Level 3
	Band[5].gear1x = 2 * typeWidth + SpaceHorizontal;
	Band[5].gear1y = 4 * levelHeight - SpaceVertical;
	Band[5].gear2x = width - SpaceHorizontal;
	
}