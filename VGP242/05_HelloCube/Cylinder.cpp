#include "Cylinder.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Input;
using namespace BOTE::Math;

#pragma region INITIALIZE
void Cylinder::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -3.0f });

	mCylinder = MeshBuilder::CreateCylinderPC(2.0f, 0.45f, 5, 16, Colors::DarkBlue);
	// -------------------------------------------
	// Create vertex buffer
	mMeshBuffer.Initialize(mCylinder);
	// -------------------------------------------
	// Compile and create vertex shader
	mVertexShader.Initialize(L"../../Assets/Shaders/DoTransform.fx", Graphics::VertexPC::Format);
	// -------------------------------------------
	// Compile and create pixel shader
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");
	// -------------------------------------------

	mTransformBuffer.Initialize();
}
#pragma endregion

#pragma region TERMINATE
void Cylinder::Terminate()
{
	// LIFO - Last In First Out
	mTransformBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}
#pragma endregion

#pragma region UPDATE
void Cylinder::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
	{
		GameApp().Quit();
		return;
	}

	const float moveSpeed = 10.0f;
	const float turnSpeed = 10.0f * Constants::DegToRad;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::UP))
		mPosition.y += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::DOWN))
		mPosition.y -= deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::RIGHT))
		mRotation.y -= deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::LEFT))
		mRotation.y += deltaTime;

	if (inputSystem->IsKeyDown(KeyCode::ONE))
		GameApp().ChangeState("Cube");
	if (inputSystem->IsKeyDown(KeyCode::TWO))
		GameApp().ChangeState("Plane");
	if (inputSystem->IsKeyDown(KeyCode::FOUR))
		GameApp().ChangeState("GameState");
	if (inputSystem->IsKeyDown(KeyCode::FIVE))
		GameApp().ChangeState("Earth");
}
#pragma endregion

#pragma region RENDER
void Cylinder::Render()
{
	mPixelShader.Bind();
	mVertexShader.Bind();

	// Setup world matrix
	Matrix4 translation = Matrix4::Translation(mPosition);
	Matrix4 rotationX = Matrix4::RotationX(mRotation.x);
	Matrix4 rotationY = Matrix4::RotationY(mRotation.y);
	Matrix4 rotationZ = Matrix4::RotationZ(mRotation.z);
	Matrix4 scale = Matrix4::Scaling(mScale);
	Matrix4 world = scale * rotationX * rotationY * rotationZ * translation;

	// Matrices must be transposed before downloading to VRAM
	TransformData transformData;
	transformData.worldMatrix = Transpose(world);
	transformData.viewMatrix = Transpose(mCamera.GetViewMatrix());
	transformData.projMatrix = Transpose(mCamera.GetProjectionMatrix());
	mTransformBuffer.Update(transformData);
	mTransformBuffer.BindVS(0);

	mMeshBuffer.Render();
}
#pragma endregion