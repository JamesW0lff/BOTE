#include "GameState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Input;
using namespace BOTE::Math;

// HLSL = High Level Shaders Language

#pragma region INITIALIZE
void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -3.0f });

	mDirectionalLight.ambient = Colors::Black;
	mDirectionalLight.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(&mCamera);
	mStandardEffect.SetDirectionalLight(&mDirectionalLight);

	mTexturingEffect.Initialize();
	mTexturingEffect.SetCamera(&mCamera);

	mSkydome.diffuseMap.Initialize("../../Assets/Images/skydome_space.jpg");
	mSkydome.depthTest = DepthStencilState::DepthTest::Disable;
	mSkydome.depthWrite = DepthStencilState::DepthWrite::Disable;
	mSkydome.meshBuffer.Initialize(MeshBuilder::CreateSkydomePX(10.0f, 256, 256));

	mEarth.material.ambient = { 0.75f, 0.75f, 0.75f, 1.0f };
	mEarth.material.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mEarth.material.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mEarth.material.power = 10.0f;

	mEarth.diffuseMap.Initialize("../../Assets/Images/earth.jpg");
	mEarth.specularMap.Initialize("../../Assets/Images/earth_spec.jpg");
	mEarth.displacementMap.Initialize("../../Assets/Images/earth_bump.jpg");
	mEarth.normalMap.Initialize("../../Assets/Images/earth_normal.jpg");
	mEarth.meshBuffer.Initialize(MeshBuilder::CreateSphere(1.0f, 512, 512));

	mCloud.material.ambient = { 0.75f, 0.75f, 0.75f, 1.0f };
	mCloud.material.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mCloud.material.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mCloud.material.power = 10.0f;
	mCloud.diffuseMap.Initialize("../../Assets/Images/earth_clouds.jpg");
	mCloud.blendMode = BlendState::Mode::Additive;
	mCloud.meshBuffer.Initialize(MeshBuilder::CreateSphere(1.2f, 512, 512));
}
#pragma endregion

#pragma region TERMINATE
void GameState::Terminate()
{
	mCloud.Terminate();
	mEarth.Terminate();
	mSkydome.Terminate();
	
	mTexturingEffect.Terminate();
	mStandardEffect.Terminate();
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
	if (inputSystem->IsKeyDown(KeyCode::D) || inputSystem->IsKeyDown(KeyCode::RIGHT))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A) || inputSystem->IsKeyDown(KeyCode::LEFT))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::R))
	{
		mCamera.SetPosition({ 0.0f, 0.0f, -3.0f });
		mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::UP))
		mCamera.Rise(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::DOWN))
		mCamera.Rise(-moveSpeed * deltaTime);

	// Make sure the Skydome is always following the camera
	mSkydome.transform.position = mCamera.GetPosition();
}
#pragma endregion

#pragma region RENDER
void GameState::Render()
{
	mTexturingEffect.Begin();
		mTexturingEffect.Render(mSkydome);
	mTexturingEffect.End();

	mStandardEffect.Begin();
		mStandardEffect.Render(mEarth);
		mStandardEffect.Render(mCloud);
	mStandardEffect.End();

	// Simple Draw
	SimpleDraw::AddTransform(Matrix4::Identity);
	
	SimpleDraw::AddFace( Vector3::Zero, Vector3::YAxis, Vector3::ZAxis, Colors::Yellow);
	
	SimpleDraw::Render(mCamera);
}
#pragma endregion

#pragma region DEBUG UI
void GameState::DebugUI()
{
	ImGui::Begin("Game Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit3("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit3("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit3("Specular##Light", &mDirectionalLight.specular.r);
		ImGui::Separator();
		if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
	}

	ImGui::Separator();
	
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit3("Ambient##Material", &mEarth.material.ambient.r);
		ImGui::ColorEdit3("Diffuse##Material", &mEarth.material.diffuse.r);
		ImGui::ColorEdit3("Specular##Material", &mEarth.material.specular.r);
		ImGui::Separator();
		ImGui::DragFloat("Power##Material", &mEarth.material.power, 0.1f, 1.0f, 100.0f);
	}

	if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Position X##Position", &mEarth.transform.position.x, 0.0f, -10.0f, 10.0f);
		ImGui::DragFloat("Position Y##Position", &mEarth.transform.position.y, 0.0f, -10.0f, 10.0f);
		ImGui::DragFloat("Position Z##Position", &mEarth.transform.position.z, 0.0f, -10.0f, 10.0f);
		if (ImGui::Button("Reset Position##Position"))
		{
			mEarth.transform.position.x = 0.0f;
			mEarth.transform.position.y = 0.0f;
			mEarth.transform.position.z = 0.0f;
		}
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Rotation", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Rotation X##Rotation", &mEarth.transform.rotation.x, 0.0f, -10.0f, 10.0f);
		ImGui::DragFloat("Rotation Y##Rotation", &mEarth.transform.rotation.y, 0.0f, -10.0f, 10.0f);
		ImGui::DragFloat("Rotation Z##Rotation", &mEarth.transform.rotation.z, 0.0f, -10.0f, 10.0f);
		if (ImGui::Button("Reset Rotation##Rotation"))
		{
			mEarth.transform.rotation.x = 0.0f;
			mEarth.transform.rotation.y = 0.0f;
			mEarth.transform.rotation.z = 0.0f;
		}
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Scale", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Scale X##Scale", &mEarth.transform.scale.x, 0.0f, 0.01f, 10.0f);
		ImGui::DragFloat("Scale Y##Scale", &mEarth.transform.scale.y, 0.0f, 0.01f, 10.0f);
		ImGui::DragFloat("Scale Z##Scale", &mEarth.transform.scale.z, 0.0f, 0.01f, 10.0f);
		if (ImGui::Button("Reset Scale##Scale"))
		{
			mEarth.transform.scale.x = 1.0f;
			mEarth.transform.scale.y = 1.0f;
			mEarth.transform.scale.z = 1.0f;
		}
	}

	ImGui::Separator();

	mStandardEffect.SEDebugUI();

	ImGui::End();
}
#pragma endregion