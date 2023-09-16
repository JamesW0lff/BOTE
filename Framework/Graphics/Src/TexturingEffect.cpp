#include "Precompiled.h"
#include "TexturingEffect.h"

// #include "BlendStateManager.h"
#include "DepthStencilStateManager.h"
#include "VertexTypes.h"

using namespace BOTE;
using namespace BOTE::Graphics;

#pragma region INITIALIZE
void TexturingEffect::Initialize()
{
	mVertexShader.Initialize(L"../../Assets/Shaders/Texturing.fx", Graphics::VertexPX::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/Texturing.fx");
	
	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Clamp);

	mTransformBuffer.Initialize();
}
#pragma endregion

#pragma region TERMINATE
void TexturingEffect::Terminate()
{
	mTransformBuffer.Terminate();

	mSampler.Terminate();

	mPixelShader.Terminate();
	mVertexShader.Terminate();
}
#pragma endregion

#pragma region BEGIN
void TexturingEffect::Begin()
{
	ASSERT(mCamera != nullptr, "Standard Effect --  no camera set!");

	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mSampler.BindPS();
}
#pragma endregion

#pragma region END
void TexturingEffect::End()
{
	DepthStencilState::ClearState();
}
#pragma endregion

#pragma region RENDER
void TexturingEffect::Render(const RenderObject& renderObject)
{
	// Global setting
	Math::Matrix4 viewMatrix = mCamera->GetViewMatrix();
	Math::Matrix4 projMatrix = mCamera->GetProjectionMatrix();

	// Setup world matrix
	Math::Matrix4 worldMatrix = renderObject.transform.GetMatrix4();

	TransformData transformData;
	transformData.wvp = Transpose(worldMatrix * viewMatrix * projMatrix);
	mTransformBuffer.Update(transformData);

	// BlendStateManager::Get()->Set(renderObject.blendMode);
	DepthStencilStateManager::Get()->Set(renderObject.depthTest, renderObject.depthWrite);

	renderObject.diffuseMap.BindPS(0);
	renderObject.meshBuffer.Render();
}
#pragma endregion

#pragma region DEBUG UI
void TexturingEffect::TEDebugUI()
{

}
#pragma endregion