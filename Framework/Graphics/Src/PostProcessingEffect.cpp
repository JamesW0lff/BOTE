#include "Precompiled.h"
#include "PostProcessingEffect.h"

#include "VertexTypes.h"

using namespace BOTE;
using namespace BOTE::Graphics;

void PostProcessingEffect::Initialize()
{
	mVertexShader.Initialize(L"../../Assets/Shaders/PostProcessing.fx", Graphics::VertexPX::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/PostProcessing.fx");

	mSampler.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);

	mSettingsBuffer.Initialize();
}

void PostProcessingEffect::Terminate()
{
	mSettingsBuffer.Terminate();

	mSampler.Terminate();

	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void PostProcessingEffect::Begin()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mSampler.BindPS(0);

	for (uint32_t i = 0; i < std::size(mTextures); ++i)
	{
		if (mTextures[i])
			mTextures[i]->BindPS(i);
	}
	
	SettingsData settingsData;
	settingsData.mode = static_cast<int>(mMode);
	settingsData.timer = mTimer;
	mSettingsBuffer.Update(settingsData);
	mSettingsBuffer.BindPS(0);
}

void PostProcessingEffect::End()
{
	for (uint32_t i = 0; i < std::size(mTextures); ++i)
	{
		if (mTextures[i])
			Texture::UnbindPS(i);
	}
}

void PostProcessingEffect::Render(const RenderObject& renderObject)
{
	renderObject.meshBuffer.Render();
}

void PostProcessingEffect::PPDebugUI()
{
	if (ImGui::CollapsingHeader("Post Processing Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int currentItem = static_cast<int>(mMode);
		const char* items[] =
		{
			"None",
			"Grayscale A",
			"Grayscale B",
			"Invert",
			"Night Vision A",
			"Night Vision B",
			"Drunk",
			"Edge Detection",
			"Bloom",
			"VHS"
		};
		if (ImGui::Combo("Mode", &currentItem, items, static_cast<int>(std::size(items))))
		{
			if (currentItem != static_cast<int>(mMode))
				mMode = static_cast<Mode>(currentItem);
		}
	}
}

void PostProcessingEffect::SetTexture(const Texture* texture, int index)
{
	mTextures[index] = texture;
}