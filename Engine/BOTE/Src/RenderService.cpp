#include "Precompiled.h"
#include "RenderService.h"

#include "AnimatorComponent.h"
#include "CameraService.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "ModelComponent.h"
#include "TerrainService.h"
#include "TransformComponent.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Math;

void RenderService::Initialize()
{
	mCameraService = GetWorld().GetService<CameraService>();
	mTerrainService = GetWorld().GetService<TerrainService>();

	mDirectionalLight.ambient = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mDirectionalLight.specular = { 0.75f, 0.75f, 0.75f, 1.0f };
	mDirectionalLight.Direction = Normalize({ 1.0f, -1.0f, 1.0f });

	mStandardEffect.Initialize();
	mStandardEffect.SetLightCamera(&mShadowEffect.GetLightCamera());
	mStandardEffect.SetDirectionalLight(&mDirectionalLight);


	mShadowEffect.Initalize();

}

void RenderService::Terminate()
{
	mShadowEffect.Terminate();
	mStandardEffect.Terminate();
}

void RenderService::Update(float deltaTime)
{
	mFPS = 1.0f / deltaTime;
}

void RenderService::Render()
{
	// Set camera
	const auto& camera = mCameraService->GetCurrentCamera();
	mStandardEffect.SetCamera(&camera);

	// Apply transform
	for (auto& entry : mRenderEntries)
	{
		Transform transform = *entry.transformComponent;
		for (auto& renderObject : entry.renderGroup)
		{
			renderObject.transform = transform;
		}
	}
}

void RenderService::DebugUI()
{
	ImGui::Begin("Render Service", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	Imgui::Text("fps: %f", mFPS);

	ImGui::Separator();

	if ()
	{

	}

	ImGui::Separator();

	mStandardEffect.DebugUI;
	mShadowEffect.DebugUI();

	ImGui::End();
}

void RenderService::Register(const ModelComponent* modelComponent)
{
	// C++17 way
	Entry& entry = mRenderEntries.emplace_back();

	auto& gameObject = modelCommponent->GetOwner();
	entry.animatorComponent = gameObject.Getcomponent<AnimatorComponent>();
	entry.modelComponent = modelComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();
	
	const Animator* animator = nullptr;
	if (entry.animatorComponent)
		animator = &entry.animatorComponent->GetAnimator();
	entry.renderGroup = CreateRenderGroup(modelComponent->GetModel());
}

void RenderService::Unregister(const ModelComponent* modelComponent)
{
	auto iter = std::find_if(
		mRenderEntries.begin(),
		mRenderEntries.end(),
		[&](const Entry& entry) {
			return entry.modelComponent == modelComponent;
		});

	if (iter != mRenderEntries.end())
	{
		Entry& entry = *iter;
		CleanUpRenderGroup(entry.renderGroup);
		mRenderEntries.erase(iter);
	}
}