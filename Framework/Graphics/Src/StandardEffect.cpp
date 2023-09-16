#include "Precompiled.h"
#include "StandardEffect.h"
#include "BlendStateManager.h"
#include "DepthStencilStateManager.h"
#include "VertexTypes.h"

using namespace BOTE;
using namespace BOTE::Graphics;

void StandardEffect::Initialize()
{
	mVertexShader.Initialize(L"../../Assets/Shaders/Standard.fx", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/Standard.fx");
	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);

	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingsBuffer.Initialize();
}

void StandardEffect::Terminate()
{
	mSettingsBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();

	mSampler.Terminate();

	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void StandardEffect::Begin()
{
	ASSERT(mCamera != nullptr, "Standard Effect --  no camera set!");
	ASSERT(mDirectionalLight != nullptr, "Standard Effect --  no light set!");

	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);
	mLightBuffer.BindPS(1);
	mMaterialBuffer.BindPS(2);
	mSettingsBuffer.BindVS(3);
	mSettingsBuffer.BindPS(3);

	mSampler.BindPS();

	mLightBuffer.Update(*mDirectionalLight); // Download from RAM to VRAM
}

void StandardEffect::End()
{
	for (uint32_t i = 0; i < 5; ++i)
		Texture::UnbindPS(i);

	BlendState::ClearState();
	DepthStencilState::ClearState();
}

void StandardEffect::Render(const RenderObject& renderObject)
{
	// Global setting
	Math::Matrix4 viewMatrix = mCamera->GetViewMatrix();
	Math::Matrix4 projMatrix = mCamera->GetProjectionMatrix();

	Math::Matrix4 worldMatrix = renderObject.transform.GetMatrix4();

	TransformData transformData;
	transformData.viewPosition = mCamera->GetPosition();
	// Draw the object
	transformData.world = Transpose(worldMatrix);
	transformData.wvp[0] = Transpose(worldMatrix * viewMatrix * projMatrix); // setting the first slot
	if (mLightCamera != nullptr) // check if we have a light camera, if so, we are using the second slot
	{
		Math::Matrix4 lightViewMatrix = mLightCamera->GetViewMatrix();
		Math::Matrix4 lightProjMatrix = mLightCamera->GetProjectionMatrix();
		transformData.wvp[1] = Transpose(worldMatrix * lightViewMatrix * lightProjMatrix);
	}
	mTransformBuffer.Update(transformData);
	mMaterialBuffer.Update(renderObject.material);

	BlendStateManager::Get()->Set(renderObject.blendMode);
	DepthStencilStateManager::Get()->Set(renderObject.depthTest, renderObject.depthWrite);

	renderObject.diffuseMap.BindPS(0);
	renderObject.specularMap.BindPS(1);
	renderObject.displacementMap.BindVS(2);
	renderObject.normalMap.BindPS(3);

	SettingsData settingsData;
	settingsData.useDiffuseMap = mSettingsData.useDiffuseMap && renderObject.diffuseMap.GetRawData();
	settingsData.useSpecularMap = mSettingsData.useSpecularMap && renderObject.specularMap.GetRawData();
	settingsData.useNormalMap = mSettingsData.useNormalMap && renderObject.normalMap.GetRawData();
	settingsData.displacementScale = renderObject.normalMap.GetRawData() ? mSettingsData.displacementScale : 0.0f;
	settingsData.useShadowMap = 0;
	if (mShadowMap != nullptr && mSettingsData.useShadowMap)
	{
		settingsData.useShadowMap = 1;
		settingsData.depthBias = mSettingsData.depthBias;
		mShadowMap->BindPS(4);
	}
	mSettingsBuffer.Update(settingsData);

	renderObject.meshBuffer.Render();
}

void StandardEffect::SEDebugUI()
{
	if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool checked = mSettingsData.useDiffuseMap == 1;
		if (ImGui::Checkbox("Diffuse Map##Settings", &checked))
			mSettingsData.useDiffuseMap = checked ? 1 : 0;

		checked = mSettingsData.useSpecularMap == 1;
		if (ImGui::Checkbox("Specular Map##Settings", &checked))
			mSettingsData.useSpecularMap = checked ? 1 : 0;

		checked = mSettingsData.useNormalMap == 1;
		if (ImGui::Checkbox("Normal Map##Settings", &checked))
			mSettingsData.useNormalMap = checked ? 1 : 0;

		checked = mSettingsData.useShadowMap == 1;
		if (ImGui::Checkbox("Shadow Map##Settings", &checked))
			mSettingsData.useShadowMap = checked ? 1 : 0;

		ImGui::DragFloat("Displacement Scale##Settings", &mSettingsData.displacementScale, 0.1f, 0.0f, 1.0f);
		ImGui::DragFloat("Depth Bias##Settings", &mSettingsData.depthBias, 0.000001f, 0.0f, 1.0f, "%.6f");
	}
}