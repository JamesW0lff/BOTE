#include "GameState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Input;
using namespace BOTE::Math;

#pragma region INITIALIZE
void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 5.0f, -15.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.ambient = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });

	mReflectionEffect.Initialize();
	mReflectionEffect.SetCamera(&mCamera);
	mReflectionEffect.SetDirectionalLight(&mDirectionalLight);

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(&mCamera);
	mStandardEffect.SetDirectionalLight(&mDirectionalLight);

	mTexturingEffect.Initialize();
	mTexturingEffect.SetCamera(&mCamera);

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(&mDirectionalLight);

	mSkydome.diffuseMap.Initialize("../../Assets/Images/skydome_day.png");
	mSkydome.depthTest = DepthStencilState::DepthTest::Disable;
	mSkydome.depthWrite = DepthStencilState::DepthWrite::Disable;
	mSkydome.meshBuffer.Initialize(MeshBuilder::CreateSkydomePX(10.0f, 256, 256));

	mGroundPlane.material.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mGroundPlane.material.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mGroundPlane.material.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mGroundPlane.material.power = 10.0f;
	mGroundPlane.diffuseMap.Initialize("../../Assets/Images/basketball_field.jpg");
	mGroundPlane.meshBuffer.Initialize(MeshBuilder::CreatePlane(25.0f, 10, 10));
	// mGroundPlane.meshBuffer.Initialize(MeshBuilder::CreatePlaneTile(25.0f, 10, 10, 5.0f));

	mSphere.transform.position = { 5.0f, 0.0f, 0.0f };
	mSphere.material.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mSphere.material.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mSphere.material.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mSphere.material.power = 10.0f;
	mSphere.diffuseMap.Initialize("../../Assets/Images/white.jpg");
	mSphere.meshBuffer.Initialize(MeshBuilder::CreateSphere(5.0f, 256, 256));

	Model palemanModel;
	ModelIO::LoadModel("../../Assets/Models/Paleman/paleman.model", palemanModel);

	mPaleman.material.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	mPaleman.material.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mPaleman.material.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mPaleman.material.power = 10.0f;
	mPaleman.diffuseMap.Initialize("../../Assets/Models/Paleman/paleman_baseColor.jpg");
	mPaleman.specularMap.Initialize("../../Assets/Models/Paleman/paleman_Emissive.jpg");
	mPaleman.normalMap.Initialize("../../Assets/Models/Paleman/paleman_normal.jpg");
	mPaleman.meshBuffer.Initialize(palemanModel.meshData[0].mesh);
}
#pragma endregion

#pragma region TERMINATE
void GameState::Terminate()
{
	mPaleman.Terminate();
	mSphere.Terminate();
	mGroundPlane.Terminate();
	mSkydome.Terminate();

	mShadowEffect.Terminate();
	mTexturingEffect.Terminate();
	mStandardEffect.Terminate();
	mReflectionEffect.Terminate();
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

	// Make sure the Skydome is always following the camera
	mSkydome.transform.position = mCamera.GetPosition();

}
#pragma endregion

#pragma region RENDER
void GameState::Render()
{
	mShadowEffect.Begin();
		mShadowEffect.Render(mPaleman);
	mShadowEffect.End();

	mReflectionEffect.Begin();
		mReflectionEffect.Render(mSphere);
	mReflectionEffect.End();

	// mTexturingEffect.Begin();
	// 	mTexturingEffect.Render(mSkydome);
	// mTexturingEffect.End();

	mStandardEffect.Begin();
		mStandardEffect.Render(mGroundPlane);
		mStandardEffect.Render(mPaleman);
	mStandardEffect.End();
		
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
		ImGui::ColorEdit3("Ambient##Material", &mPaleman.material.ambient.r);
		ImGui::ColorEdit3("Diffuse##Material", &mPaleman.material.diffuse.r);
		ImGui::ColorEdit3("Specular##Material", &mPaleman.material.specular.r);
		ImGui::Separator();
		ImGui::DragFloat("Power##Material", &mPaleman.material.power, 0.1f, 1.0f, 100.0f);
	}

 	ImGui::Separator();

	if (ImGui::CollapsingHeader("Scale", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Scale X##Scale", &mPaleman.transform.scale.x, 0.0f, 0.01f, 10.0f);
		ImGui::DragFloat("Scale Y##Scale", &mPaleman.transform.scale.y, 0.0f, 0.01f, 10.0f);
		ImGui::DragFloat("Scale Z##Scale", &mPaleman.transform.scale.z, 0.0f, 0.01f, 10.0f);
		if (ImGui::Button("Reset Scale"))
		{
			mPaleman.transform.scale.x = 0.25f;
			mPaleman.transform.scale.y = 0.25f;
			mPaleman.transform.scale.z = 0.25f;
		}
	}

 	ImGui::Separator();

	mStandardEffect.SEDebugUI();

	ImGui::Separator();

	mShadowEffect.DebugSEUI();

	ImGui::End();
}
#pragma endregion