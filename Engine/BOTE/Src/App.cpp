#include "Precompiled.h"
#include "App.h"

#include "AppState.h"

using namespace BOTE;

#pragma region CHANGE STATE
void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}
#pragma endregion

#pragma region RUN
void App::Run(AppConfig appConfig)
{
	Core::Window window;
	window.Initialize(
		GetModuleHandle(nullptr), 
		appConfig.appName.c_str(), 
		appConfig.windowWidth, appConfig.windowHeight);

	// Initialize engine systems
	auto handle = window.GetWindowHandle();
	Input::InputSystem::StaticInitialize(handle);
	Graphics::GraphicsSystem::StaticInitialize(window.GetWindowHandle(), false);
	Graphics::BlendStateManager::StaticInitialize();
	Graphics::DepthStencilStateManager::StaticInitialize();
	Graphics::TextureManager::StaticInitialize();
	Graphics::DebugUI::StaticInitialize(handle, false, true);
	Graphics::SimpleDraw::StaticInitialize(appConfig.debugDrawLimit);

	ASSERT(mCurrentState, "App -- No app state found!");
	mCurrentState->Initialize();

	mRunning = true;
	while (mRunning)
	{
		window.ProcessMessage();
		if (!window.IsActive())
			break; // Exit if our window is destroyed

		if (mNextState)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		auto inputSystem = Input::InputSystem::Get();
		inputSystem->Update(); // refresh input device state

		auto deltaTime = Core::TimeUtil::GetDeltaTimeSeconds();
		mCurrentState->Update(deltaTime);

		auto graphicsSystem = Graphics::GraphicsSystem::Get();
		graphicsSystem->BeginRender();

		mCurrentState->Render();
		
		// Hooking up Debug UI
		Graphics::DebugUI::BeginRender();
		mCurrentState->DebugUI();
		Graphics::DebugUI::EndRender();

		graphicsSystem->EndRender();
	}

	mCurrentState->Terminate();

	// Shutdown engine systems
	Graphics::SimpleDraw::StaticTerminate();
	Graphics::DebugUI::StaticTerminate();
	Graphics::TextureManager::StaticTerminate();
	Graphics::BlendStateManager::StaticTerminate();
	Graphics::DepthStencilStateManager::StaticTerminate();
	Graphics::GraphicsSystem::StaticTerminate();
	Input::InputSystem::StaticTerminate();

	window.Terminate();
}
#pragma endregion

#pragma region QUIT
void App::Quit()
{
	mRunning = false;
}
#pragma endregion