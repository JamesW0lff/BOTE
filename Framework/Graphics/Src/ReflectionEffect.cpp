#include "Precompiled.h"
#include "ReflectionEffect.h"

#include "BlendStateManager.h"
#include "DepthStencilStateManager.h"
#include "VertexTypes.h"

using namespace BOTE;
using namespace BOTE::Graphics;

#pragma region INITIALIZE
void ReflectionEffect::Initialize()
{
	mVertexShader.Initialize(L"../../Assets/Shaders/ReflectionShader.fx", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/ReflectionShader.fx");
	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);

	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingsBuffer.Initialize();
}
#pragma endregion

#pragma region TERMINATE
void ReflectionEffect::Terminate()
{
	mSettingsBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();

	mSampler.Terminate();

	mPixelShader.Terminate();
	mVertexShader.Terminate();
}
#pragma endregion

#pragma region BEGIN
void ReflectionEffect::Begin()
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

	// Download from RAM to VRAM
	mLightBuffer.Update(*mDirectionalLight);
}
#pragma endregion

#pragma region END
void ReflectionEffect::End()
{
	BlendState::ClearState();
	DepthStencilState::ClearState();
}
#pragma endregion

#pragma region RENDER
void ReflectionEffect::Render(const RenderObject& renderObject)
{
	// Global setting
	Math::Matrix4 viewMatrix = mCamera->GetViewMatrix();
	Math::Matrix4 projMatrix = mCamera->GetProjectionMatrix();

	// Setup world matrix
	Math::Matrix4 translation = Math::Matrix4::Translation(renderObject.transform.position);
	Math::Matrix4 rotationX = Math::Matrix4::RotationX(renderObject.transform.rotation.x);
	Math::Matrix4 rotationY = Math::Matrix4::RotationY(renderObject.transform.rotation.y);
	Math::Matrix4 rotationZ = Math::Matrix4::RotationZ(renderObject.transform.rotation.z);
	Math::Matrix4 scale = Math::Matrix4::Scaling(renderObject.transform.scale);
	Math::Matrix4 worldMatrix = scale * rotationX * rotationY * rotationZ * translation;

	TransformData transformData;
	transformData.viewPosition = mCamera->GetPosition();
	// Draw the object
	transformData.world = Transpose(worldMatrix);
	transformData.wvp = Transpose(worldMatrix * viewMatrix * projMatrix);
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
	settingsData.displacementScale = mSettingsData.displacementScale ? mSettingsData.displacementScale : 0.0f;
	mSettingsBuffer.Update(settingsData);

	renderObject.meshBuffer.Render();
}
#pragma endregion

#pragma region DEBUG UI
void ReflectionEffect::REDebugUI()
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

		ImGui::DragFloat("Displacement Scale##Settings", &mSettingsData.displacementScale, 0.1f, 0.0f, 1.0f);
	}
}
#pragma endregion