#include "CircleState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Math;

#pragma region INITIALIZE
void CircleState::Initialize()
{
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->SetClearColor(Graphics::Colors::OrangeRed);

	radius = 0.5f;
	mCircleVertex = 6;

	increment = (2.0f * BOTE::Math::Constants::PI) / mCircleVertex;

	for (int i = 0; i < mCircleVertex; ++i)
	{
		mVertices.push_back({ Vector3{ 0.0f,  0.0f, 0.0f }, Colors::Yellow });

		mVertices.push_back({ Vector3{	radius * sinf(increment * i), 
										radius * cosf(increment * i), 
										0.0f }, 
										Colors::YellowGreen });

		mVertices.push_back({ Vector3{	radius * sinf(increment * (i + 1)), 
										radius * cosf(increment * (i + 1)), 
										0.0f }, 
										Colors::YellowGreen });
	}

	// float x;
	// float y;
	// https://stackoverflow.com/questions/33858753/drawing-a-circle-using-opengl-c
	// for (float currAngle = 0.0f; currAngle <= 2.0f * PI; currAngle += increment)
	// {
	// 	mVertices.push_back({ Vector3{ radius * cosf(currAngle) + x, 
	//							radius * sinf(currAngle) + y, 
	//							0.0f }, 
	//							Colors::Blue });
	// }

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
void CircleState::Terminate()
{
	// LIFO - Last In First Out
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}
#pragma endregion

#pragma region UPDATE
void CircleState::Update(float deltaTime)
{
	if (GetAsyncKeyState(VK_ESCAPE))
		GameApp().Quit();
	if (GetAsyncKeyState('1'))
		GameApp().ChangeState("HeartState");
	if (GetAsyncKeyState('3'))
		GameApp().ChangeState("ShapeState");
}
#pragma endregion

#pragma region RENDER
void CircleState::Render()
{
	mPixelShader.Bind();
	mVertexShader.Bind();
	mMeshBuffer.Render();
}
#pragma endregion