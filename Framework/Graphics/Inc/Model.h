#pragma once

#include "Material.h"
#include "MeshTypes.h"

namespace BOTE::Graphics
{
	struct Model
	{
		struct MeshData
		{
			Mesh mesh;
			uint32_t materialIndex = 0;
		};

		struct MaterialData
		{
			Material material;
			std::string diffuseMapName;
			std::string specularMapName;
			std::string displacementMapName;
			std::string normalMapName;
		};

		std::vector<MeshData> meshData;
		std::vector<MaterialData> materialData;
	};
}