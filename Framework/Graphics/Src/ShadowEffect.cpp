#include "Precompiled.h"
#include "ShadowEffect.h"

#include "VertexTypes.h"

using namespace BOTE;
using namespace BOTE::Graphics;

void ShadowEffect::Initialize()
{
	mLightCamera.SetMode(Camera::ProjectionMode::Orthographic);

	constexpr uint32_t depthMapSize = 4096;
	mDepthMapRenderTarget.Initialize(depthMapSize, depthMapSize, Texture::Format::RGBA_U32);

	mVertexShader.Initialize(L"../../Assets/Shaders/Shadow.fx", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/Shadow.fx");

	mTransformBuffer.Initialize();
}

void ShadowEffect::Terminate()
{
	mTransformBuffer.Terminate();

	mPixelShader.Terminate();
	mVertexShader.Terminate();

	mDepthMapRenderTarget.Terminate();
}

void ShadowEffect::Begin()
{
	const auto direction = mDirectionalLight->direction;
	mLightCamera.SetDirection(direction);
	mLightCamera.SetPosition(mFocusPosition - (direction * 1000.0f));
	mLightCamera.SetNearPlane(1.0f);
	mLightCamera.SetFarPlane(1500.0f);
	mLightCamera.SetSize(mSize, mSize);

	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mDepthMapRenderTarget.BeginRender();
}

void ShadowEffect::End()
{
	mDepthMapRenderTarget.EndRender();
}

void ShadowEffect::Render(const RenderObject& renderObject)
{
	Math::Matrix4 translation = Math::Matrix4::Translation(renderObject.transform.position);
	Math::Matrix4 rotationX = Math::Matrix4::RotationX(renderObject.transform.rotation.x);
	Math::Matrix4 rotationY = Math::Matrix4::RotationY(renderObject.transform.rotation.y);
	Math::Matrix4 rotationZ = Math::Matrix4::RotationZ(renderObject.transform.rotation.z);
	Math::Matrix4 scale = Math::Matrix4::Scaling(renderObject.transform.scale);
	Math::Matrix4 world = scale * rotationX * rotationY * rotationZ * translation;

	Math::Matrix4 view = mLightCamera.GetViewMatrix();
	Math::Matrix4 proj = mLightCamera.GetProjectionMatrix();

	TransformData transformData;
	transformData.wvp = Math::Transpose(world * view * proj);
	mTransformBuffer.Update(transformData);

	renderObject.meshBuffer.Render();
}

void ShadowEffect::DebugSEUI()
{
	if (ImGui::CollapsingHeader("Shadow Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Image(
			mDepthMapRenderTarget.GetRawData(),
			{ 150.0f, 150.0f },
			{ 0.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f }
		);
	}
}