#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "Material.h"
#include "PixelShader.h"
#include "RenderObject.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace BOTE::Graphics
{
	class StandardEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);
		void SEDebugUI();

		void SetCamera(const Camera* camera) { mCamera = camera; }
		void SetLightCamera(const Camera* camera) { mLightCamera = camera; }
		void SetDirectionalLight(const DirectionalLight* light) { mDirectionalLight = light; }
		void SetShadowMap(const Texture* shadowMap) { mShadowMap = shadowMap; }

		void SetDepthBias(float bias) { mSettingsData.depthBias = bias; }

	private:
		
		struct TransformData
		{
			Math::Matrix4 world;
			Math::Matrix4 wvp[2]; // world view projection
			Math::Vector3 viewPosition;
			float padding = 0.0f;
		};

		struct SettingsData
		{
			// We use an integer to represent a bool in the Shaders side
			int useDiffuseMap = 1;
			int useSpecularMap = 1;
			int useNormalMap = 1;
			float displacementScale = 0.2f;

			int useShadowMap = 1; // bool in HLSL is 4 byte, therefore we use an int here
			float depthBias = 0.0f; // ConstantBuffer.h Initialize -> 16 bytes per row
			float padding[2] = {}; // padding to keep the struct 16-byte aligned to match VRAM
		};

		// To guarantee that the camera & light will NOT be changed
		const Camera* mCamera = nullptr;
		const Camera* mLightCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;
		const Texture* mShadowMap = nullptr;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		Sampler mSampler;

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using LightBuffer = TypedConstantBuffer<BOTE::Graphics::DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<BOTE::Graphics::Material>;
		using SettingsBuffer = TypedConstantBuffer<SettingsData>;

		TransformBuffer mTransformBuffer;
		LightBuffer mLightBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingsBuffer mSettingsBuffer;

		SettingsData mSettingsData;
	};
}