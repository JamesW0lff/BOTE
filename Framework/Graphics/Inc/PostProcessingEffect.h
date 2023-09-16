#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "RenderObject.h"
#include "Sampler.h"
#include "Texture.h"
#include "VertexShader.h"

namespace BOTE::Graphics
{
	class PostProcessingEffect
	{
	public:
		enum class Mode
		{
			None,
			GrayscaleA,
			GrayscaleB,
			Invert,
			NightVisionA,
			NightVisionB,
			Drunk,
			EdgeDetection,
			Bloom,
			VHS
		};

		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);
		void PPDebugUI();

		void SetTexture(const Texture* texture, int index);
		void SetMode(Mode mode) { mMode = mode; }
		void SetTimer(float timer) { mTimer = timer; }

	private:
		struct SettingsData
		{
			int mode = 0;
			float timer = 0.0f;
			float padding[2] = {};
		};

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		const Texture* mTextures[2] = {};
		Sampler mSampler;

		using SettingsBuffer = TypedConstantBuffer<SettingsData>;

		SettingsBuffer mSettingsBuffer;

		Mode mMode = Mode::None;
		float mTimer = 0.0f;
		float mPixelation = 1.0f;
	};
}