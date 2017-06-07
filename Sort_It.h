#pragma once  //______________________________________ Sort_It.h  
#include "Resource.h"
#include "Gear.h"
#include "Box.h"
#include "Bandx.h"

#define DEFAULTH 50
#define DEFAULTV 10
#define GearSpeed 250
#define GearDiameter 15

class Sort_It : public Game::Window
{
public:
	Sort_It()
	{
	}
	~Sort_It()
	{
	}


	Gear Gear[12];
	Bandx Band[6];
	Box Box[20];



	void PaintBands(CG::Gdi gdi, float delta, float typewidth, float levelHeight, float SpaceVertical, float SpaceHorizontal);
	void ChangeDirection(int x, int y);
	void DefineBandPosition(float typeWidth, float levelHeight, float SpaceVertical, float SpaceHorizontal);
	void MoveBox(double x, double y, float delta, CG::Gdi gdi);

	//int BandNumber;

	CG::DDBitmap BitmapBG;
	//CG::DDBitmap BitmapBM;

	Sys::Icon Icon;
	//HINSTANCE hInstance;



	bool RenderScene(CG::Gdi& gdi);
	const wchar_t * GetClassName() { return L"Sort_It"; }
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	void InitializeGui()
	{
		this->Text = L"Sort_It";
	}
	//void Window_KeyDown(Win::Event& e);
	//void Window_KeyUp(Win::Event& e);
	void Window_LButtonDown(Win::Event& e);
	//void Window_LButtonUp(Win::Event& e);
	//void Window_MouseMove(Win::Event& e);
	//void Window_Size(Win::Event& e);
	void Window_Open(Win::Event& e);
	void GetWindowInformation(CREATESTRUCT& createStruct)
	{
		createStruct.style = WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
	}
	bool EventHandler(Win::Event& e)
	{
		return false;
	}
};
