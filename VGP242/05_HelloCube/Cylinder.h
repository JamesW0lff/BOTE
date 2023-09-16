#pragma once

#include <BOTE/Inc/BOTE.h>

class Cylinder : public BOTE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;

private:
	struct TransformData
	{
		BOTE::Math::Matrix4 worldMatrix;
		BOTE::Math::Matrix4 viewMatrix;
		BOTE::Math::Matrix4 projMatrix;
	};

	BOTE::Graphics::Camera mCamera;
	BOTE::Graphics::MeshPC mCylinder;

	BOTE::Graphics::MeshBuffer mMeshBuffer;
	BOTE::Graphics::VertexShader mVertexShader;
	BOTE::Graphics::PixelShader mPixelShader;

	using TransformBuffer = BOTE::Graphics::TypedConstantBuffer<TransformData>;
	TransformBuffer mTransformBuffer;

	BOTE::Math::Vector3 mPosition = BOTE::Math::Vector3::Zero;
	BOTE::Math::Vector3 mRotation = BOTE::Math::Vector3::Zero;
	BOTE::Math::Vector3 mScale = BOTE::Math::Vector3::One;
};