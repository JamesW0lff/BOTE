#include "ShapeState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Math;

#pragma region INITIALIZE
void ShapeState::Initialize()
{
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->SetClearColor(Graphics::Colors::Red);

	radius = 0.8f;
	mCircleVertex = 50;

	increment = (2.0f * PI) / mCircleVertex;

	// ------- LEFT -------
	// Triangle 1
	mVertices.push_back({ Vector3{ -0.2f, 0.6f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.35f, -0.5f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.6f, -0.4f, 0.0f }, Colors::Red });

	// Triangle 2
	mVertices.push_back({ Vector3{ -0.2f, 0.6f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.0f, 0.0f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.3f, 0.3f, 0.0f }, Colors::Red });

	// Triangle 3
	mVertices.push_back({ Vector3{ 0.0f, 0.2f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.0f, 0.0f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ -0.2f, 0.6f, 0.0f }, Colors::Red });

	// ------- RIGHT -------
	// Triangle 4
	mVertices.push_back({ Vector3{ 0.0f, 0.2f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.2f, 0.6f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.0f, 0.0f, 0.0f }, Colors::Red });

	// Triangle 5
	mVertices.push_back({ Vector3{ 0.2f, 0.6f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.3f, 0.3f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.0f, 0.0f, 0.0f }, Colors::Red });

	// Triangle 6
	mVertices.push_back({ Vector3{ 0.2f, 0.6f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.6f, -0.4f, 0.0f }, Colors::Red });
	mVertices.push_back({ Vector3{ 0.35f, -0.5f, 0.0f }, Colors::Red });

	// Circle
	for (int i = 0; i < mCircleVertex; ++i)
	{
		mVertices.push_back({ Vector3{ 0.0f,  0.0f, 0.0f }, Colors::White });

		mVertices.push_back({ Vector3{	radius * sinf(increment * i),
										radius * cosf(increment * i),
										0.0f },
										Colors::White });

		mVertices.push_back({ Vector3{	radius * sinf(increment * (i + 1)),
										radius * cosf(increment * (i + 1)),
										0.0f },
										Colors::White });
	}

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
void ShapeState::Terminate()
{
	// LIFO - Last In First Out
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}
#pragma endregion

#pragma region UPDATE
void ShapeState::Update(float deltaTime)
{
	if (GetAsyncKeyState(VK_ESCAPE))
		GameApp().Quit();
	if (GetAsyncKeyState('1'))
		GameApp().ChangeState("HeartState");
	if (GetAsyncKeyState('2'))
		GameApp().ChangeState("CircleState");
}
#pragma endregion

#pragma region RENDER
void ShapeState::Render()
{
	mPixelShader.Bind();
	mVertexShader.Bind();
	mMeshBuffer.Render();
}
#pragma endregion