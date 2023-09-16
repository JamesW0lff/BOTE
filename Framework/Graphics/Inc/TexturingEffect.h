#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "RenderObject.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace BOTE::Graphics
{
	class TexturingEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);
		void TEDebugUI();

		void SetCamera(const Camera* camera) { mCamera = camera; }

	private:
		struct TransformData
		{
			Math::Matrix4 wvp; // world view projection
		};

		const Camera* mCamera = nullptr;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		Sampler mSampler;

		using TransformBuffer = TypedConstantBuffer<TransformData>;

		TransformBuffer mTransformBuffer;
	};
}