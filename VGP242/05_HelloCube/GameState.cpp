#include "GameState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Input;
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

	mCamera.SetPosition({ 0.0f, 0.0f, -3.0f });

	// TODO:: Fill cube vertices and indices
	/*mCube.vertices.push_back({Vector3{1.0f, 1.0f, 0.0f}, Colors::Red});						// 0
	mCube.vertices.push_back({ Vector3{ 1.0f, -1.0f, 0.0f }, Colors::Green }); // Duplicated	// 1
	mCube.vertices.push_back({ Vector3{ -1.0f, 1.0f, 0.0f }, Colors::Blue }); // Duplicated 2	// 2
	
	// mCube.vertices.push_back({ Vector3{ 0.5f, 0.0f, 0.0f }, Colors::Green }); // Duplicated	 // 1
	mCube.vertices.push_back({ Vector3{ -1.0f, -1.0f, 0.0f }, Colors::Yellow });					 // 3
	// mCube.vertices.push_back({ Vector3{ -0.5f, 0.0f, 0.0f }, Colors::Blue }); // Duplicated 2 // 2

	mCube.vertices.push_back({ Vector3{1.0f, 1.0f, -1.0f }, Colors::Orange });  // 4
	mCube.vertices.push_back({ Vector3{1.0f, -1.0f, -1.0f }, Colors::Cyan }); // 5

	mCube.vertices.push_back({ Vector3{-1.0f, 1.0f, -1.0f}, Colors::Brown });		// 6
	mCube.vertices.push_back({ Vector3{-1.0f, -1.0f, -1.0f}, Colors::Purple });	// 7
	
	// Alternate way to push back indices
	mCube.indices = 
	{
		0,1,2,1,3,2,
		4,5,0,5,1,0,
		6,7,4,7,5,4,
		2,3,6,3,7,6,
		4,0,6,0,2,6,
		1,5,3,5,7,3
	};
	*/
	// FRONT
	// mCube.indices.push_back(0);
	// mCube.indices.push_back(1);
	// mCube.indices.push_back(2);
	 
	// mCube.indices.push_back(1);
	// mCube.indices.push_back(3);
	// mCube.indices.push_back(2);
	 
	// // RIGHT
	// mCube.indices.push_back(4);
	// mCube.indices.push_back(5);
	// mCube.indices.push_back(0);
	 
	// mCube.indices.push_back(5);
	// mCube.indices.push_back(1);
	// mCube.indices.push_back(0);
	 
	// // BACK
	// mCube.indices.push_back(6);
	// mCube.indices.push_back(7);
	// mCube.indices.push_back(4);
	 
	// mCube.indices.push_back(7);
	// mCube.indices.push_back(5);
	// mCube.indices.push_back(4);
	 
	// // LEFT
	// mCube.indices.push_back(2);
	// mCube.indices.push_back(3);
	// mCube.indices.push_back(6);
	 
	// mCube.indices.push_back(3);
	// mCube.indices.push_back(7);
	// mCube.indices.push_back(6);
	 
	// // TOP
	// mCube.indices.push_back(4);
	// mCube.indices.push_back(0);
	// mCube.indices.push_back(6);
	 
	// mCube.indices.push_back(0);
	// mCube.indices.push_back(2);
	// mCube.indices.push_back(6);
	 
	// // BOTTOM
	// mCube.indices.push_back(1);
	// mCube.indices.push_back(5);
	// mCube.indices.push_back(3);
	 
	// mCube.indices.push_back(5);
	// mCube.indices.push_back(7);
	// mCube.indices.push_back(3);

	// mCube = MeshBuilder::CreateCubePC(Colors::Red);

	// size, rows, columns
	mSphere = MeshBuilder::CreateSpherePC(1.0f, 16, 16, Colors::Aquamarine);
	// mCube = MeshBuilder::CreateCylinderPC(4, 1, 5, 5, Colors::DarkBlue);
	// -------------------------------------------
	// Create vertex buffer
	mMeshBuffer.Initialize(mSphere);
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
void GameState::Terminate()
{
	// LIFO - Last In First Out
	mTransformBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}
#pragma endregion

#pragma region UPDATE
void GameState::Update(float deltaTime)
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
	if(inputSystem->IsKeyDown(KeyCode::DOWN))
		mPosition.y -= deltaTime;
	if(inputSystem->IsKeyDown(KeyCode::RIGHT))
		mRotation.y -= deltaTime;
	if(inputSystem->IsKeyDown(KeyCode::LEFT))
		mRotation.y += deltaTime;

	if (inputSystem->IsKeyDown(KeyCode::ONE))
		GameApp().ChangeState("Cube");
	if (inputSystem->IsKeyDown(KeyCode::TWO))
		GameApp().ChangeState("Plane");
	if (inputSystem->IsKeyDown(KeyCode::THREE))
		GameApp().ChangeState("Cylinder");
	if (inputSystem->IsKeyDown(KeyCode::FIVE))
		GameApp().ChangeState("Earth");
}
#pragma endregion

#pragma region RENDER
void GameState::Render()
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