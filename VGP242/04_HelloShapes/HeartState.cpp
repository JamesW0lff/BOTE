#include "HeartState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Math;

#pragma region INITIALIZE
void HeartState::Initialize()
{
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->SetClearColor(Graphics::Colors::MediumPurple);

	// ------- LEFT -------
	mVertices.push_back({ Vector3{  0.0f,  0.50f, 0.0f }, Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.0f,  -0.50f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{  -0.4f,  0.0f, 0.0f }, Colors::Red });

	mVertices.push_back({ Vector3{  0.0f,  0.50f, 0.0f }, Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.4f,  0.0f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{  -0.4f,  0.5f, 0.0f }, Colors::Red });

	mVertices.push_back({ Vector3{  0.0f,  0.50f, 0.0f }, Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.4f,  0.5f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{  -0.3f,  0.75f, 0.0f }, Colors::Red });

	mVertices.push_back({ Vector3{  0.0f,  0.50f, 0.0f }, Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.3f,  0.75f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{  -0.1f,  0.75f, 0.0f }, Colors::Red });

	// ------- RIGHT -------
	mVertices.push_back({ Vector3{  0.0f,  0.50f, 0.0f }, Colors::DarkBlue });
	mVertices.push_back({ Vector3{  0.1f,  0.75f, 0.0f }, Colors::Blue });
	mVertices.push_back({ Vector3{  0.3f,  0.75f, 0.0f }, Colors::Blue });

	mVertices.push_back({ Vector3{  0.0f,  0.50f, 0.0f }, Colors::DarkBlue });
	mVertices.push_back({ Vector3{  0.3f,  0.75f, 0.0f }, Colors::Blue });
	mVertices.push_back({ Vector3{  0.4f,  0.50f, 0.0f }, Colors::Blue });

	mVertices.push_back({ Vector3{  0.0f,  0.50f, 0.0f }, Colors::DarkBlue });
	mVertices.push_back({ Vector3{  0.4f,  0.50f, 0.0f }, Colors::Blue });
	mVertices.push_back({ Vector3{  0.4f,  0.0f, 0.0f }, Colors::Blue });

	mVertices.push_back({ Vector3{  0.0f,  0.50f, 0.0f }, Colors::DarkBlue });
	mVertices.push_back({ Vector3{  0.4f,  0.0f, 0.0f }, Colors::Blue });
	mVertices.push_back({ Vector3{  0.0f,  -0.50f, 0.0f }, Colors::Blue });

	// -------------------------------------------
	// Create vertex buffer
	mMeshBuffer.Initialize(mVertices.data(), sizeof(Graphics::VertexPC), (uint32_t)mVertices.size());
	// -------------------------------------------
	// Compile and create vertex shader
	mVertexShader.Initialize(L"../../Assets/Shaders/DoColor.fx", Graphics::VertexPC::Format);
	// -------------------------------------------
	// Compile and create pixel shader
	mPixelShader.Initialize(L"../../Assets/Shaders/DoColor.fx");
	// -------------------------------------------
}
#pragma endregion

#pragma region TERMINATE
void HeartState::Terminate()
{
	// LIFO - Last In First Out
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}
#pragma endregion

#pragma region UPDATE
void HeartState::Update(float deltaTime)
{
	if (GetAsyncKeyState(VK_ESCAPE))
		GameApp().Quit();
	if (GetAsyncKeyState('2'))
		GameApp().ChangeState("CircleState");
	if (GetAsyncKeyState('3'))
		GameApp().ChangeState("ShapeState");
}
#pragma endregion

#pragma region RENDER
void HeartState::Render()
{
	mPixelShader.Bind();
	mVertexShader.Bind();
	mMeshBuffer.Render();
}
#pragma endregion