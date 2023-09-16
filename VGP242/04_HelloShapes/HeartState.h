#pragma once

#include <BOTE/Inc/BOTE.h>

class HeartState : public BOTE::AppState
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
};