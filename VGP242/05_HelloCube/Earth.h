#pragma once

#include <BOTE/Inc/BOTE.h>

class Earth : public BOTE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;

private:
	struct TransformData
	{
		BOTE::Math::Matrix4 world;
		BOTE::Math::Matrix4 wvp;
		BOTE::Math::Matrix4 viewPosition;
	};

	BOTE::Graphics::Camera mCamera;
	BOTE::Graphics::MeshPX mEarthMesh;

	BOTE::Graphics::MeshBuffer mEarthMeshBuffer;

	BOTE::Graphics::VertexShader mTexturingVertexShader;
	BOTE::Graphics::PixelShader mTexturingPixelShader;

	BOTE::Graphics::Texture mEarthTexture;
	BOTE::Graphics::Sampler mSampler;

	using TransformBuffer = BOTE::Graphics::TypedConstantBuffer<TransformData>;
	TransformBuffer mTransformBuffer;

	BOTE::Math::Vector3 mPosition = BOTE::Math::Vector3::Zero;
	BOTE::Math::Vector3 mRotation = BOTE::Math::Vector3::Zero;
	BOTE::Math::Vector3 mScale = BOTE::Math::Vector3::One;
};