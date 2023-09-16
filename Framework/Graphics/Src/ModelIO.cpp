#include "Precompiled.h"
#include "ModelIO.h"

#include "Model.h"

using namespace BOTE;
using namespace BOTE::Graphics;

void ModelIO::SaveModel(std::filesystem::path filePath, const Model& model)
{
	if (model.meshData.empty())
		return;

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
		return;

	const uint32_t meshCount = static_cast<uint32_t>(model.meshData.size());
	fprintf_s(file, "MeshCount: %d\n", meshCount);
	for (uint32_t i = 0; i < meshCount; ++i)
	{
		const auto& meshData = model.meshData[i];
		fprintf_s(file, "MaterialIndex: %d\n", meshData.materialIndex);

		const auto& mesh = meshData.mesh;
		const uint32_t vertexCount = static_cast<uint32_t>(mesh.vertices.size());
		fprintf_s(file, "VertexCount: %d\n", vertexCount);

		for (auto& vertex : mesh.vertices)
		{
			fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
				vertex.position.x, vertex.position.y, vertex.position.z,
				vertex.normal.x, vertex.normal.y, vertex.normal.z,
				vertex.tangent.x, vertex.tangent.y, vertex.tangent.z,
				vertex.texCoord.x, vertex.texCoord.y
			);
		}

		const uint32_t indexCount = static_cast<uint32_t>(mesh.indices.size());
		fprintf_s(file, "IndexCount: %d\n", indexCount);

		for (size_t i = 0; i < indexCount; i += 3)
		{
			fprintf_s(file, "%d %d %d\n",
				mesh.indices[i],
				mesh.indices[i + 1u],
				mesh.indices[i + 2u]);
		}
	}

	fclose(file);
}

void ModelIO::LoadModel(std::filesystem::path filePath, Model& model)
{
	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
		return;

	uint32_t meshCount = 0;
	fscanf_s(file, "MeshCount: %d\n", &meshCount);

	model.meshData.resize(meshCount);
	for (uint32_t i = 0; i < meshCount; ++i)
	{
		auto& meshData = model.meshData[i];
		fscanf_s(file, "MaterialIndex: %d\n", &meshData.materialIndex);

		auto& mesh = meshData.mesh;

		uint32_t vertexCount = 0;
		fscanf_s(file, "VertexCount: %d\n", &vertexCount);
		mesh.vertices.resize(vertexCount);

		for (auto& vertex : mesh.vertices)
		{
			fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
				&vertex.position.x, &vertex.position.y, &vertex.position.z,
				&vertex.normal.x, &vertex.normal.y, &vertex.normal.z,
				&vertex.tangent.x, &vertex.tangent.y, &vertex.tangent.z,
				&vertex.texCoord.x, &vertex.texCoord.y
			);
		}

		uint32_t indexCount = 0;
		fscanf_s(file, "IndexCount: %d\n", &indexCount);
		mesh.indices.resize(indexCount);

		for (size_t i = 0; i < indexCount; i += 3)
		{
			fscanf_s(file, "%d %d %d\n",
				&mesh.indices[i],
				&mesh.indices[i + 1u],
				&mesh.indices[i + 2u]);
		}
	}

	fclose(file);
}