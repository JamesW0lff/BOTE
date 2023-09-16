#pragma once

#include <BOTE/Inc/BOTE.h>

class GameState : public BOTE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;

private:
	struct Vertex
	{
		BOTE::Math::Vector3 position;
		BOTE::Graphics::Color color;
	};

	std::vector<Vertex> mVertices;

	BOTE::Graphics::MeshBuffer mMeshBuffer;

	// TODO: Move these pointers into Graphics::Vertex
	BOTE::Graphics::VertexShader mVertexShader;

	// TODO: Move this into Graphics::PixelShader
	BOTE::Graphics::PixelShader mPixelShader;
};

// About GraphicsSystem:
// ====================
// This is a singleton primarily manages two Direct3D interface pointers, namely>
//
// ID3D11Device} GetDevice* ();
// ID3D11DeviceContext* GetContext();
//
// The devide pointer represents the current configuration active for the GPU
// This will be the pointer used for allocating graphics memory.