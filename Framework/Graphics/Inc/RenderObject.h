#pragma once

#include "BlendState.h"
#include "DepthStencilState.h"
#include "Material.h"
#include "MeshBuffer.h"
#include "Texture.h"
#include "Transform.h"

namespace BOTE::Graphics
{
	class RenderObject final
	{
	public:
		void Terminate()
		{
			normalMap.Terminate();
			displacementMap.Terminate();
			specularMap.Terminate();
			diffuseMap.Terminate();
			meshBuffer.Terminate();
		}

		Transform transform;
		Material material;

		// Object Textures
		Texture diffuseMap;
		Texture specularMap;
		Texture displacementMap;
		Texture normalMap;

		BlendState::Mode blendMode = BlendState::Mode::Opaque;

		DepthStencilState::DepthTest depthTest = DepthStencilState::DepthTest::Enable;
		DepthStencilState::DepthWrite depthWrite = DepthStencilState::DepthWrite::Enable;

		MeshBuffer meshBuffer;
	};
}