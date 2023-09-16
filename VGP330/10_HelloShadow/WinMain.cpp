#include "GameState.h"

using namespace BOTE;

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig appConfig;
	appConfig.appName = L"Hello Shadow";
	appConfig.windowWidth = 1280;
	appConfig.windowHeight = 720;
	appConfig.debugDrawLimit = 100000;

	GameApp().AddState<GameState>("GameState");

	BOTE::GameApp().Run(appConfig);

	return 0;
}
#pragma endregion