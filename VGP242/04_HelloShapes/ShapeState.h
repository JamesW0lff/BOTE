#pragma once

#include <BOTE/Inc/BOTE.h>

class ShapeState : public BOTE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;

private:
	std::vector<BOTE::Graphics::VertexPC> mVertices;

	BOTE::Graphics::MeshBuffer mMeshBuffer;
	BOTE::Graphics::VertexShader mVertexShader;
	BOTE::Graphics::PixelShader mPixelShader;

	int mCircleVertex = 0;

	const float PI = 3.1415926f;

	float radius = 0.0f;
	float increment = 0.0f;
};