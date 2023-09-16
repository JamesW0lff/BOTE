#include "Cube.h"
#include "Plane.h"
#include "Cylinder.h"
#include "GameState.h"
#include "Earth.h"

using namespace BOTE;

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	GameApp().AddState<Cube>("Cube");
	GameApp().AddState<Plane>("Plane");
	GameApp().AddState<Cylinder>("Cylinder");
	GameApp().AddState<GameState>("GameState");
	GameApp().AddState<Earth>("Earth");
	
	BOTE::GameApp().Run({ L"Hello Cube" });

	return 0;
} // Destructor will be called here
#pragma endregion