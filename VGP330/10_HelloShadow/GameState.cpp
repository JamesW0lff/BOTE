#include "GameState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Input;
using namespace BOTE::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 5.0f, -15.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.ambient = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(&mCamera);
	mStandardEffect.SetLightCamera(&mShadowEffect.GetLightCamera());
	mStandardEffect.SetDirectionalLight(&mDirectionalLight);
	mStandardEffect.SetShadowMap(&mShadowEffect.GetDepthMap());
	mStandardEffect.SetDepthBias(0.00001f);

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(&mDirectionalLight);

	mGroundPlane.material.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mGroundPlane.material.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mGroundPlane.material.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mGroundPlane.material.power = 10.0f;
	mGroundPlane.diffuseMap.Initialize("../../Assets/Images/basketball_field.jpg");
	mGroundPlane.meshBuffer.Initialize(MeshBuilder::CreatePlane(25.0f, 10, 10));

	mBall.material.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mBall.material.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mBall.material.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mBall.material.power = 10.0f;
	mBall.diffuseMap.Initialize("../../Assets/Images/basketball.png");
	mBall.meshBuffer.Initialize(MeshBuilder::CreateSphere(1.0f, 128, 128));

	Model duckModel;
	ModelIO::LoadModel("../../Assets/Models/Duck/duck.model", duckModel);

	mDuck.material.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mDuck.material.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDuck.material.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDuck.material.power = 10.0f;
	mDuck.diffuseMap.Initialize("../../Assets/Models/Duck/duck.png");
	mDuck.meshBuffer.Initialize(duckModel.meshData[0].mesh);
}

void GameState::Terminate()
{
	mDuck.Terminate();
	mBall.Terminate();
	mGroundPlane.Terminate();

	mShadowEffect.Terminate();
	mStandardEffect.Terminate();
}

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
	if (inputSystem->IsKeyDown(KeyCode::R))
	{
		mCamera.SetPosition({ 0.0f, 5.0f, -15.0f });
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

	if (inputSystem->IsKeyPressed(KeyCode::PAUSE))
		mPause = !mPause;
	if (mPause)
		deltaTime = 0.0f;

	static float time = 0.0f;
	time += deltaTime;
	
	mBall.transform.position.y = 1.0f + abs(sinf(time * mBounceSpeed)) * 3.0f; // Bouncing the ball

	mDuck.transform.position.x = cosf(time * mDuckSpeed) * 5.0f;
	mDuck.transform.position.z = sinf(time * mDuckSpeed) * 5.0f;
	mDuck.transform.rotation = Quaternion::RotationAxis(Vector3::YAxis, -time - Constants::HalfPI);
}

void GameState::Render()
{
	mShadowEffect.Begin();
		mShadowEffect.Render(mBall);
		mShadowEffect.Render(mDuck);
	mShadowEffect.End();

	mStandardEffect.Begin();
		mStandardEffect.Render(mGroundPlane);
		mStandardEffect.Render(mBall);
		mStandardEffect.Render(mDuck);
	mStandardEffect.End();
		
	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::AddFace( Vector3::Zero, Vector3::YAxis, Vector3::ZAxis, Colors::Yellow);
	SimpleDraw::Render(mCamera);
}

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
	
	if (ImGui::CollapsingHeader("Speed Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Ball Speed", &mBounceSpeed, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("Duck Speed", &mDuckSpeed, 0.1f, 0.0f, 10.0f);
	}
	ImGui::Separator();
	
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit3("Ambient##Material", &mBall.material.ambient.r);
		ImGui::ColorEdit3("Diffuse##Material", &mBall.material.diffuse.r);
		ImGui::ColorEdit3("Specular##Material", &mBall.material.specular.r);
		ImGui::Separator();
		ImGui::DragFloat("Power##Material", &mBall.material.power, 0.1f, 1.0f, 100.0f);
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Scale", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Scale X##Scale", &mBall.transform.scale.x, 0.0f, 0.01f, 15.0f);
		ImGui::DragFloat("Scale Y##Scale", &mBall.transform.scale.y, 0.0f, 0.01f, 15.0f);
		ImGui::DragFloat("Scale Z##Scale", &mBall.transform.scale.z, 0.0f, 0.01f, 15.0f);
		if (ImGui::Button("Reset Scale##Scale"))
		{
			mBall.transform.scale.x = 1.0f;
			mBall.transform.scale.y = 1.0f;
			mBall.transform.scale.z = 1.0f;
		}
	}

	ImGui::Separator();

	mStandardEffect.SEDebugUI();

	ImGui::Separator();

	mShadowEffect.DebugSEUI();

	ImGui::End();
}