#include "Earth.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Input;
using namespace BOTE::Math;

// HLSL = High Level Shaders Language

#pragma region INITIALIZE
void Earth::Initialize()
{

	mCamera.SetPosition({ 0.0f, 0.0f, -3.0f });

	// size, rows, columns
	mEarthMesh = MeshBuilder::CreateSpherePX(1.0f, 16, 16);
	// mCube = MeshBuilder::CreateCylinderPC(4, 1, 5, 5, Colors::DarkBlue);
	// -------------------------------------------
	// Create vertex buffer
	mEarthMeshBuffer.Initialize(mEarthMesh);
	// -------------------------------------------
	// Compile and create vertex shader
	mTexturingVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", Graphics::VertexPX::Format);
	// -------------------------------------------
	// Compile and create pixel shader
	mTexturingPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");
	// -------------------------------------------

	mEarthTexture.Initialize("../../Assets/Images/earth.jpg");
	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Clamp);

	mTransformBuffer.Initialize();
}
#pragma endregion

#pragma region TERMINATE
void Earth::Terminate()
{
	// LIFO - Last In First Out
	mTransformBuffer.Terminate();

	mSampler.Terminate();
	mEarthTexture.Terminate();

	mTexturingPixelShader.Terminate();
	mTexturingVertexShader.Terminate();

	mEarthMeshBuffer.Terminate();
}
#pragma endregion

#pragma region UPDATE
void Earth::Update(float deltaTime)
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
	if (inputSystem->IsKeyDown(KeyCode::THREE))
		GameApp().ChangeState("Cylinder");
	if (inputSystem->IsKeyDown(KeyCode::FOUR))
		GameApp().ChangeState("GameState");
}
#pragma endregion

#pragma region RENDER
void Earth::Render()
{
	mTexturingPixelShader.Bind();
	mTexturingVertexShader.Bind();
	mEarthTexture.BindPS();
	mSampler.BindPS();

	// Setup world matrix
	Matrix4 translation = Matrix4::Translation(mPosition);
	Matrix4 rotationX = Matrix4::RotationX(mRotation.x);
	Matrix4 rotationY = Matrix4::RotationY(mRotation.y);
	Matrix4 rotationZ = Matrix4::RotationZ(mRotation.z);
	Matrix4 scale = Matrix4::Scaling(mScale);
	Matrix4 world = scale * rotationX * rotationY * rotationZ * translation;

	// Matrices must be transposed before downloading to VRAM
	TransformData transformData;
	transformData.world = Transpose(world);
	transformData.wvp = Transpose(mCamera.GetViewMatrix());
	transformData.viewPosition = Transpose(mCamera.GetProjectionMatrix());
	mTransformBuffer.Update(transformData);
	mTransformBuffer.BindVS(0);

	mEarthMeshBuffer.Render();
}
#pragma endregion