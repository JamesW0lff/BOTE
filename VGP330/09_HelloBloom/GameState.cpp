#include "GameState.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Input;
using namespace BOTE::Math;

#pragma region INITIALIZE
void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -15.0f });

	mDirectionalLight.ambient = Colors::Black;
	mDirectionalLight.diffuse = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });

	auto gs = GraphicsSystem::Get();
	const auto screenWidth = gs->GetBackBufferWidth();
	const auto screenHeight = gs->GetBackBufferHeight();
	mBaseRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
	mBloomRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(&mCamera);
	mStandardEffect.SetDirectionalLight(&mDirectionalLight);

	mTexturingEffect.Initialize();
	mTexturingEffect.SetCamera(&mCamera);

	mGaussianBlurEffect.Initialize();
	mGaussianBlurEffect.SetSourceTexture(mBloomRenderTarget);
	mGaussianBlurEffect.SetBlurIterations(10);
	mGaussianBlurEffect.SetBlurSaturation(1.0f);
	
	mPostProcessingEffect.Initialize();
	mPostProcessingEffect.SetTexture(&mBaseRenderTarget, 0);
	mPostProcessingEffect.SetTexture(&mGaussianBlurEffect.GetResultTexture(), 1);

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
	mCloud.meshBuffer.Initialize(MeshBuilder::CreateSphere(1.2f, 256, 256));

	mSun.diffuseMap.Initialize("../../Assets/Images/sun.jpg");
	mSun.meshBuffer.Initialize(MeshBuilder::CreateSpherePX(5.0f, 256, 256));

	mScreenQuad.meshBuffer.Initialize(MeshBuilder::CreateNDCQuad());

	mEarthDistance = 8.0f;
}
#pragma endregion

#pragma region TERMINATE
void GameState::Terminate()
{
	mScreenQuad.Terminate();

	mSun.Terminate();
	mCloud.Terminate();
	mEarth.Terminate();
	mSkydome.Terminate();
	
	mPostProcessingEffect.Terminate();
	mGaussianBlurEffect.Terminate();
	mTexturingEffect.Terminate();
	mStandardEffect.Terminate();

	mBloomRenderTarget.Terminate();
	mBaseRenderTarget.Terminate();
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
		mCamera.SetPosition({ 0.0f, 0.0f, -15.0f });
		mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	// Make sure the Skydome is always following the camera
	mSkydome.transform.position = mCamera.GetPosition();

	if (inputSystem->IsKeyDown(KeyCode::UP))
		mEarthRevolution += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::DOWN))
		mEarthRevolution -= deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::RIGHT))
		mEarthRotation -= deltaTime;
	if(inputSystem->IsKeyDown(KeyCode::LEFT))
		mEarthRotation += deltaTime;

	mCloudRotation += deltaTime * 0.01f;

	mEarth.transform.position = TransformCoord({ 0.0f, 0.0f, -mEarthDistance }, Matrix4::RotationY(mEarthRevolution));
	mEarth.transform.rotation = Quaternion::RotationAxis(Vector3::XAxis, mEarthRotation);

	mCloud.transform = mEarth.transform;
	mCloud.transform.rotation *= Quaternion::RotationAxis(Vector3::YAxis, mCloudRotation);

	static float timer = 0.0f;
	timer += deltaTime;
	mPostProcessingEffect.SetTimer(timer);
}
#pragma endregion

#pragma region RENDER
void GameState::Render()
{
	// Capture Scene
	mBaseRenderTarget.BeginRender();
		mTexturingEffect.Begin();
			mTexturingEffect.Render(mSkydome);
			mTexturingEffect.Render(mSun);
		mTexturingEffect.End();

		mStandardEffect.Begin();
			mStandardEffect.Render(mEarth);
			mStandardEffect.Render(mCloud);
		mStandardEffect.End();
		
		SimpleDraw::AddTransform(Matrix4::Identity);
		
		SimpleDraw::AddFace( Vector3::Zero, Vector3::YAxis, Vector3::ZAxis, Colors::Yellow);
		
		SimpleDraw::Render(mCamera);
	mBaseRenderTarget.EndRender();
	
	// Draw brightness
	mBloomRenderTarget.BeginRender();
		mStandardEffect.Begin();
			// Remember the material of the Earth
			auto originalMaterial = mEarth.material;
			mEarth.material.ambient = Colors::Black;
			mEarth.material.diffuse = Colors::Black;
			mEarth.material.specular = Colors::Black;
			mStandardEffect.Render(mEarth);
			mEarth.material = originalMaterial;
		mStandardEffect.End();
		mTexturingEffect.Begin();
			mTexturingEffect.Render(mSun);
		mTexturingEffect.End();
	mBloomRenderTarget.EndRender();

	// Apply blur
	mGaussianBlurEffect.Begin();
		mGaussianBlurEffect.Render(mScreenQuad);
	mGaussianBlurEffect.End();

	// Post Process
	mPostProcessingEffect.Begin();
		mPostProcessingEffect.Render(mScreenQuad);
	mPostProcessingEffect.End();
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

	if (ImGui::CollapsingHeader("Earth", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Distance##Earth", &mEarthDistance, 0.1f);
		ImGui::DragFloat("Rotation##Earth", &mEarthRotation, 0.1f);
		ImGui::DragFloat("Revolution##Earth", &mEarthRevolution, 0.1f);
	}

	ImGui::Separator();

	mStandardEffect.SEDebugUI();

	ImGui::Separator();

	mGaussianBlurEffect.GBEDebugUI();

	ImGui::Separator();
	
	mPostProcessingEffect.PPDebugUI();

	ImGui::End();

	ImGui::Begin("Render Targets", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Base");
	ImGui::Image(mBaseRenderTarget.GetRawData(), { 256.0f, 144.0f });
	ImGui::Text("Bloom");
	ImGui::Image(mBloomRenderTarget.GetRawData(), { 256.0f, 144.0f });
	ImGui::Text("Horizontal Blur");
	ImGui::Image(mGaussianBlurEffect.GetHorizontalBlurTexture().GetRawData(), { 256.0f, 144.0f });
	ImGui::Text("Vertical Blur");
	ImGui::Image(mGaussianBlurEffect.GetVerticalBlurTexture().GetRawData(), { 256.0f, 144.0f });
	ImGui::End();
}
#pragma endregion