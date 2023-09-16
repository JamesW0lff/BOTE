#include "BOTE/Inc/BOTE.h"

using namespace BOTE;

class GameState1 : public BOTE::AppState 
{
public:
	void Initialize() override
	{
		auto graphicsSystem = Graphics::GraphicsSystem::Get();
		graphicsSystem->SetClearColor(Graphics::Colors::BlanchedAlmond);
	}

	void Update(float deltaTime) override
	{
		if (GetAsyncKeyState(VK_ESCAPE))
			GameApp().Quit();
		if (GetAsyncKeyState('2'))
			GameApp().ChangeState("GameState2");
	}
};

class GameState2 : public BOTE::AppState
{
public:
	void Initialize() override
	{
		auto graphicsSystem = Graphics::GraphicsSystem::Get();
		graphicsSystem->SetClearColor(Graphics::Colors::Red);
	}

	void Update(float deltaTime) override
	{
		if (GetAsyncKeyState(VK_ESCAPE))
			GameApp().Quit();
		if (GetAsyncKeyState('1'))
			GameApp().ChangeState("GameState1");
	}
};

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	GameApp().AddState<GameState1>("GameState1");
	GameApp().AddState<GameState2>("GameState2");
	// Method # 1 - Intialize config directly
	// BOTE::AppConfig config;
	// config.appName = L"Hello Direct X";
	// config.windowHeight = 800;
	// config.windowWidth = 1000;
	// 
	// BOTE::GameApp().Run(config);

	// Method # 2 - Default initialization
	// BOTE::GAmeApp().Run({});

	// Method # 3 - Agregate initialization
	BOTE::GameApp().Run({ L"Hello Direct X" });

	return 0;
}
#pragma endregion