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
	
	this->Show(SW_SHOWMAXIMIZED);//para hacer grande la pantalla
}

bool Sort_It::RenderScene(CG::Gdi& gdi)
{
	static DWORD prevTime = timeGetTime();
	const DWORD currentTime = timeGetTime();
	const float delta = (currentTime - prevTime) / 1000.0f;

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


	///	double x, y;
	int  SPACE = GearDiameter + BandGrosor + 2;
	int  SPACEboxR = SPACE + BoxSize;

	//____________________BOXES
	
	//Band 0
	if (Box[0].PrimerMovimiento == true)
	{
		if (Box[0].left >= Band[0].gear2x + SPACE && Box[0].left <= Band[0].gear2x + SPACEboxR && Box[0].BandNumber == 0)
		{
			Box[0].BandNumber++;
		}
		Box[0].DrawBox(gdi, delta, false);

	}

	if (Box[0].bottom >= Band[1].gear1y - SPACE  && Box[0].BandNumber == 1)
	{
		Box[0].PrimerMovimiento = false;
		Box[0].DrawBox(gdi, delta, Band[1].esDerecha);
		//______Limite Izquierdo_Banda 1
		if (Box[0].left >= Band[1].gear1x - SPACEboxR && Box[0].left <= Band[1].gear1x - SPACE && Box[0].BandNumber == 1)
			Box[0].BandNumber++;
		//______Limite Derecho_Banda 1
		//if (Box[0].left >= Band[1].gear2x + SPACE && Box[0].left <= Band[1].gear2x + SPACE + BoxSize&& Box[0].BandNumber == 1)
	}

	//______Limite Izquierdo_Banda 1
	if (Box[0].left >= Band[1].gear1x - SPACEboxR && Box[0].left <= Band[1].gear1x - SPACE && Box[0].BandNumber == 1 && Box[0].BandNumber == 2)
	{
		Box[0].Caida = true;
	}
		
		

		//this->Text = L"Derecha?: ";
		//this->Text += Sys::Convert::ToString(Band[1].esDerecha);
		////this->Text += L" ,Primer Movimiento?: ";
		////this->Text += Sys::Convert::ToString(Box[0].PrimerMovimiento);
		this->Text = Sys::Convert::ToString(Box[0].BandNumber);
	


	
	//MoveBox(box.left, box.bottom, delta,gdi);

	


	prevTime = timeGetTime();
	return true; // return false to stop
}

void Sort_It::MoveBox(double x,double y,float delta,CG::Gdi gdi)//left,bottom
{
	//Box=i,j=band
	double SPACE = GearDiameter + BandGrosor;
	for (x = Band[0].gear1x; x <= Band[0].gear2x + SPACE; x += GearSpeed/2)
	{
		Box[0].left = x;
		Box[0].bottom = y;
		//Box[0].DrawBox(gdi, 2, false,delta);

	}
		//gdi.Rectangle(box);
	/*for (y = Band[0].gear1y; y <= Band[1].gear1y - SPACE; x += GearSpeed*delta)
		gdi.Rectangle(box);*/



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


//____________________Define Gears Position
////_________Band 0 _______Level 0
////Gear [0]
//GearsX[0] = (2 * BoxSize + 15) / 2.0;
//GearsY[0] = 2.45 * BoxSize;
////Gear [1]
//GearsX[1] = width / 2;
//GearsY[1] = GearsY[0];
////_________Band 1 _______Level 1
////Gear [2]
//GearsX[2] = typeWidth + SpaceHorizontal;
//GearsY[2] = 2 * levelHeight - SpaceVertical;
////Gear [3]
//GearsX[3] = 2.5*typeWidth - SpaceHorizontal;
//GearsY[3] = GearsY[2];
////________Band 2 _______Level 2
////Gear [4]
//GearsX[4] = 0.5*typeWidth + SpaceHorizontal;
//GearsY[4] = 3 * levelHeight - SpaceVertical;
////Gear [5]
//GearsX[5] = 1.5*typeWidth - SpaceHorizontal;
//GearsY[5] = GearsY[4];
////_________Band 3 _______Level 3
////Gear [6]
//GearsX[6] = SpaceHorizontal;
//GearsY[6] = 4 * levelHeight - SpaceVertical;
////Gear [7]
//GearsX[7] = typeWidth - SpaceHorizontal;
//GearsY[7] = GearsY[6];
////_________Band 4 _______Level 3
////Gear [8]
//GearsX[8] = typeWidth + SpaceHorizontal;
//GearsY[8] = 4 * levelHeight - SpaceVertical;
////Gear [9]
//GearsX[9] = 2 * typeWidth - SpaceHorizontal;
//GearsY[9] = GearsY[8];
////_________Band 5 _______Level 3
////Gear [10]
//GearsX[10] = 2 * typeWidth + SpaceHorizontal;
//GearsY[10] = 4 * levelHeight - SpaceVertical;
////Gear [11]
//GearsX[11] = width - SpaceHorizontal;
//GearsY[11] = GearsY[10];