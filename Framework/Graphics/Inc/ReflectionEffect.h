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
	class ReflectionEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);
		void REDebugUI();

		void SetCamera(const Camera* camera) { mCamera = camera; }

		void SetDirectionalLight(const DirectionalLight* directionalLight) { mDirectionalLight = directionalLight; }

	private:

		struct TransformData
		{
			Math::Matrix4 world;
			Math::Matrix4 wvp; // world view projection
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
		};

		// To guarantee that the camera & light will NOT be changed
		const Camera* mCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;

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