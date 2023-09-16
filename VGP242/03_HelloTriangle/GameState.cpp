#include "GameState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Math;

// HLSL = High Level Shaders Language

#pragma region INITIALIZE
void GameState::Initialize()
{
	// Setting up memory in C++
	// NDC - Normalized Device Coordinate
	//
	//          +-----------------+
	//         /                 /|
	//   1.0  +-----------------+ |
	//	      |        ^        | |
	//	      |        |        | |
	//	      | <------+------> | |
	//	      |        |        | | 1.0
	//	      |        v        |/
	//	-1.0  +-----------------+ 0.0
	//      -1.0               1.0
	//
	mVertices.push_back({ Vector3{ 0.0f, 0.5f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.5f, -0.5f, 0.0f }, Colors::Green });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.0f }, Colors::Blue });

	// -------------------------------------------
	// Create vertex buffer
	mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), (uint32_t)mVertices.size());
	// -------------------------------------------
	// Compile and create vertex shader
	mVertexShader.Initialize(L"../../Assets/Shaders/DoColor.fx", true);
	// -------------------------------------------
	// Compile and create pixel shader
	mPixelShader.Initialize(L"../../Assets/Shaders/DoColor.fx");
	// -------------------------------------------
}
#pragma endregion

#pragma region TERMINATE
void GameState::Terminate()
{
	// LIFO - Last In First Out
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}
#pragma endregion

#pragma region UPDATE
void GameState::Update(float deltaTime)
{
	if (GetAsyncKeyState(VK_ESCAPE))
		GameApp().Quit();
}
#pragma endregion

#pragma region RENDER
void GameState::Render()
{
	mPixelShader.Bind();
	mVertexShader.Bind();
	mMeshBuffer.Render();
}
#pragma endregion