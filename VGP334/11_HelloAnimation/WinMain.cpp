#include "GameState.h"

using namespace BOTE;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig appConfig;
	appConfig.appName = L"Hello Animation";
	appConfig.windowWidth = 1280;
	appConfig.windowHeight = 720;
	appConfig.debugDrawLimit = 900000;

	GameApp().AddState<GameState>("GameState");
	BOTE::GameApp().Run(appConfig);
	return 0;
}