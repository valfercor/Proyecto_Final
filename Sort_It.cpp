#include "stdafx.h"  //________________________________________ Sort_It.cpp
#include "Sort_It.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR cmdLine, int cmdShow) {
	Sort_It app;
	app.CreateMainWindow(L"Sort_It", cmdShow, IDI_Sort_It, NULL, (HBRUSH)::GetStockObject(NULL_BRUSH), hInstance);
	return app.MessageLoop(IDC_Sort_It);
}

void Sort_It::Window_Open(Win::Event& e)
{
	////________Background
	//BitmapBG.CreateFromResource(this->hInstance, IDB_BACKGROUND);

	//tbxOutput.Visible = false;

	this->Show(SW_SHOWMAXIMIZED);//para hacer grande la pantalla
}

bool Sort_It::RenderScene(CG::Gdi& gdi)
{
	static DWORD prevTime = timeGetTime();
	const DWORD currentTime = timeGetTime();
	const float delta = (currentTime - prevTime) / 1000.0f;

	float levelHeight = (height - (BoxSize + 2 * DEFAULTV)) / 4;
	float typeWidth = width / 3;
	//______________ Update the game


	//____________________________________________ Paint Window Background
	CG::Brush brush(RGB(100, 100, 255));
	RECT rect = { 0, 0, width, height };
	gdi.FillRect(rect, brush);

	//____________________________________________ Paint Machine

	RECT box;
	box.bottom = 0;
	box.left = 0;
	box.right = 2 * BoxSize;
	box.top = 3 * BoxSize;
	gdi.Rectangle(box);
	float SpaceHorizontal = BoxSize + DEFAULTH + BandSpace + (GearRadio / 2);
	float SpaceVertical = DEFAULTV + BandSpace + (GearRadio / 2);

	//____________________________________________ Paint Band
	Band[1].DrawBand(gdi, 1.5*typeWidth - SpaceHorizontal, 2 * levelHeight - SpaceVertical, 2.5*typeWidth - SpaceHorizontal, 2 * levelHeight - SpaceVertical,GearRadio);
	Band[2].DrawBand(gdi, typeWidth - SpaceHorizontal, 3 * levelHeight - SpaceVertical, 1.5*typeWidth - SpaceHorizontal, 3 * levelHeight - SpaceVertical,GearRadio);
	Band[3].DrawBand(gdi, SpaceHorizontal, 4 * levelHeight - SpaceVertical, typeWidth - SpaceHorizontal, 4 * levelHeight - SpaceVertical,GearRadio);
	Band[3].DrawBand(gdi, typeWidth + SpaceHorizontal, 4 * levelHeight - SpaceVertical, 2 * typeWidth - SpaceHorizontal, 4 * levelHeight - SpaceVertical,GearRadio);
	Band[3].DrawBand(gdi, 2 * typeWidth + SpaceHorizontal, 4 * levelHeight - SpaceVertical, width - SpaceHorizontal, 4 * levelHeight - SpaceVertical,GearRadio);

	//____________________________________________ Paint Gears


	// Level 0
	Gear[0].DrawGear(gdi, (box.right - box.left) / 2.0 , 2 * BoxSize);
	Gear[1].DrawGear(gdi, width / 2, levelHeight - SpaceVertical);

	//2nd Level
	Gear[2].DrawGear(gdi, 1.5*typeWidth - SpaceHorizontal, 2 * levelHeight - SpaceVertical);
	Gear[3].DrawGear(gdi, 2.5*typeWidth - SpaceHorizontal, 2 * levelHeight - SpaceVertical);

	//2nd Level
	Gear[4].DrawGear(gdi, typeWidth - SpaceHorizontal, 3 * levelHeight - SpaceVertical);
	Gear[5].DrawGear(gdi, 1.5*typeWidth - SpaceHorizontal, 3 * levelHeight - SpaceVertical);

	//3rd level
	Gear[6].DrawGear(gdi, SpaceHorizontal, 4 * levelHeight - SpaceVertical);
	Gear[7].DrawGear(gdi, typeWidth - SpaceHorizontal, 4 * levelHeight - SpaceVertical);
	Gear[8].DrawGear(gdi, typeWidth + SpaceHorizontal, 4 * levelHeight - SpaceVertical);
	Gear[9].DrawGear(gdi, 2 * typeWidth - SpaceHorizontal, 4 * levelHeight - SpaceVertical);
	Gear[10].DrawGear(gdi, 2 * typeWidth + SpaceHorizontal, 4 * levelHeight - SpaceVertical);
	Gear[12].DrawGear(gdi, width - SpaceHorizontal, 4 * levelHeight - SpaceVertical);

	





		prevTime = timeGetTime();
	return true; // return false to stop
}


//void Sort_It::Window_Size(Win::Event& e)
//{
//	Game::Window::Window_Size(e);
//	// Use this->width and this->height
//}

//void Sort_It::Window_KeyDown(Win::Event& e)
//{
//	switch (e.wParam)
//	{
//	case VK_SHIFT:
//		break;
//	case VK_UP:
//		break;
//	case 'A':
//		break;
//	}
//}

//void Sort_It::Window_KeyUp(Win::Event& e)
//{
//	switch (e.wParam)
//	{
//	case VK_SHIFT:
//		break;
//	case VK_UP:
//		break;
//	case 'A':
//		break;
//	}
//}

//void Sort_It::Window_LButtonDown(Win::Event& e)
//{
//	const int x = GET_X_LPARAM(e.lParam);
//	const int y = GET_Y_LPARAM(e.lParam);
//	this->SetFocus();
//}

//void Sort_It::Window_LButtonUp(Win::Event& e)
//{
//	const int x = GET_X_LPARAM(e.lParam);
//	const int y = GET_Y_LPARAM(e.lParam);
//}

//void Sort_It::Window_MouseMove(Win::Event& e)
//{
//	const int x = GET_X_LPARAM(e.lParam);
//	const int y = GET_Y_LPARAM(e.lParam);
//}

