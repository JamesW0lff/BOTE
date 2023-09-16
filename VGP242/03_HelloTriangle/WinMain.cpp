#include "GameState.h"

using namespace BOTE;

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	GameApp().AddState<GameState>("GameState");
	
	BOTE::GameApp().Run({ L"Hello Triangle" });

	return 0;
}
#pragma endregion