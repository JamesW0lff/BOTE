#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace BOTE;
using namespace BOTE::Graphics;
using namespace BOTE::Math;

#pragma region CREATE CUBE PC
MeshPC MeshBuilder::CreateCubePC(Color color)
{
	MeshPC mesh;

	// Peter's Code
	mesh.vertices.push_back({ Vector3{ -1.0f, -1.0f, -1.0f }, color });
	mesh.vertices.push_back({ Vector3{ -1.0f, +1.0f, -1.0f }, color });
	mesh.vertices.push_back({ Vector3{ +1.0f, +1.0f, -1.0f }, color });
	mesh.vertices.push_back({ Vector3{ +1.0f, -1.0f, -1.0f }, color });

	mesh.vertices.push_back({ Vector3{ -1.0f, -1.0f, +1.0f }, color });
	mesh.vertices.push_back({ Vector3{ -1.0f, +1.0f, +1.0f }, color });
	mesh.vertices.push_back({ Vector3{ +1.0f, +1.0f, +1.0f }, color });
	mesh.vertices.push_back({ Vector3{ +1.0f, -1.0f, +1.0f }, color });

	// Peter's code
	mesh.indices =
	{
		0, 1, 2, 0, 2, 3,
		3, 2, 6, 3, 6, 7,
		7, 6, 5, 7, 5, 4,
		4, 5, 1, 4, 1, 0,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};

	return mesh;
}
#pragma endregion

#pragma region CREATE PLANE PC
MeshPC MeshBuilder::CreatePlanePC(float size, int rows, int columns, Color color)
{
	MeshPC mesh;

	if (size != columns)
		size = columns;
	
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			float x{ static_cast<float>(c) };
			float y{ 0.0f };
			float z{ static_cast<float>(r) };

			mesh.vertices.push_back({ {x, y, z}, color });
		}
	}

	for (int r = 0; r + 1 < rows; ++r)
	{
		for (int c = 0; c + 1 < columns; ++c)
		{
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
		}
	}

	return mesh;
}
#pragma endregion

#pragma region CREATE CYLINDER PC
MeshPC MeshBuilder::CreateCylinderPC(float height, float radius, int rings, int slices, Color color)
{
	MeshPC mesh;
	
	const int rows{ rings + 2 };
	const int columns{ slices + 1 };

	const float yStep = height / (rings - 1.0f);
	const float yOffset = height * -0.5f;

	const float thetaStep{ Constants::TwoPI / slices };

	for (int r = 0; r < rows; ++r)
	{
		// We move y here because the height will always be the same
		float y{ ((static_cast<float>(r) - 1) * yStep) + yOffset };
		float ringRadius{ radius };

		if (r == 0)
		{
			y = yOffset;
			ringRadius = 0.0f;
		}
		else if (r + 1 == rows)
		{
			y = height + yOffset;
			ringRadius = 0.0f;
		}

		for (int s = 0; s < columns; ++s)
		{
			float theta{ s * thetaStep };
			float x{ -sinf(theta) * ringRadius };
			float z{ cosf(theta) * ringRadius };

			mesh.vertices.push_back({ {x, y, z}, color });
		}
	}

	for (int r = 0; r + 1 < rows; ++r)
	{
		for (int c = 0; c + 1 < columns; ++c)
		{
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));

			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
		}
	}

	return mesh;
}
#pragma endregion

#pragma region CREATE SPHERE PC
MeshPC MeshBuilder::CreateSpherePC(float radius, int rings, int slices, Color color)
{
	MeshPC mesh;

	const int rows{ rings };
	const int columns{ slices + 1 };

	float phiStep{ Constants::PI / (rings - 1) };
	float thetaStep{ Constants::TwoPI / slices };

	for (int r = 0; r < rows; ++r)
	{
		const float phi{ r * phiStep };
		float y{ -cosf(phi) * radius };
		float ringRadius{ sinf(phi) * radius };

		for (int s = 0; s < columns; ++s)
		{
			float theta{ s * thetaStep };
			float x{ -sinf(theta) * ringRadius };
			float z{ cosf(theta) * ringRadius };

			mesh.vertices.push_back({ {x, y, z}, color });
		}
	}

	for (int r = 0; r + 1 < rows; ++r)
	{
		for (int c = 0; c + 1 < columns; ++c)
		{
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));

			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
		}
	}

	return mesh;
}
#pragma endregion

#pragma region CREATE SPHERE PX
MeshPX MeshBuilder::CreateSpherePX(float radius, int rings, int slices)
{
	MeshPX mesh;

	const int rows{ rings };
	const int columns{ slices + 1 };

	const float phiStep{ Constants::PI / (rings - 1) };
	const float thetaStep{ Constants::TwoPI / slices };

	// const float uStep{ 1.0f / slices };
	const float uStep{ 1.0f / columns };
	const float vStep{ 1.0f / (rings - 1.0f) };

	for (int r = 0; r < rows; ++r)
	{
		const float phi{ r * phiStep };
		float y{ -cosf(phi) * radius };
		float ringRadius{ sinf(phi) * radius };

		for (int s = 0; s < columns; ++s)
		{
			float theta{ s * thetaStep };
			float x{ -sinf(theta) * ringRadius };
			float z{ cosf(theta) * ringRadius };
			const float u{ s * uStep };
			const float v{ 1.0f - (r * vStep) };

			mesh.vertices.push_back({ {x, y, z}, { u, v } });
		}
	}

	for (int r = 0; r + 1 < rows; ++r)
	{
		for (int c = 0; c + 1 < columns; ++c)
		{
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));

			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
		}
	}

	return mesh;
}
#pragma endregion

#pragma region CREATE SKYDOME PX
MeshPX MeshBuilder::CreateSkydomePX(float radius, int rings, int slices)
{
	MeshPX mesh;

	const int rows{ rings };
	const int columns{ slices + 1 };

	const float phiStep{ Constants::PI / (rings - 1) };
	const float thetaStep{ Constants::TwoPI / slices };

	const float uStep{ 1.0f / slices };
	const float vStep{ 1.0f / (rings - 1.0f) };

	for (int r = 0; r < rows; ++r)
	{
		const float phi{ r * phiStep };
		float y{ -cosf(phi) * radius };
		float ringRadius{ sinf(phi) * radius };

		for (int s = 0; s < columns; ++s)
		{
			float theta{ s * thetaStep };
			float x{ -sinf(theta) * ringRadius };
			float z{ cosf(theta) * ringRadius };
			const float u{ s * uStep };
			const float v{ 1.0f - (r * vStep) };

			mesh.vertices.push_back({ {x, y, z}, { u, v } });
		}
	}

	for (int r = 0; r + 1 < rows; ++r)
	{
		for (int c = 0; c + 1 < columns; ++c)
		{
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			mesh.indices.push_back((c + 0) + ((r + 1) * columns));

			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
		}
	}

	return mesh;
}
#pragma endregion

#pragma region CREATE NDC QUAD
MeshPX MeshBuilder::CreateNDCQuad()
{
	MeshPX mesh;

	mesh.vertices = 
	{
		{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } }, // Bottom Left
		{ { -1.0f, +1.0f, 0.0f }, { 0.0f, 0.0f } }, // Top Left
		{ { +1.0f, +1.0f, 0.0f }, { 1.0f, 0.0f } }, // Top Right
		{ { +1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } }  // Bottom Right
	};

	mesh.indices = 
	{
		0, 1, 2, 0, 2, 3
	};

	return mesh;
}
#pragma endregion

#pragma region CREATE SPHERE
Mesh MeshBuilder::CreateSphere(float radius, int rings, int slices)
{
	Mesh mesh;

	const int rows{ rings };
	const int columns{ slices + 1 };

	const float phiStep{ Constants::PI / (rings - 1) };
	const float thetaStep{ Constants::TwoPI / slices };

	const float uStep{ 1.0f / slices };
	const float vStep{ 1.0f / (rings - 1.0f) };

	for (int r = 0; r < rows; ++r)
	{
		const float phi{ r * phiStep };
		float y{ -cosf(phi) * radius };
		float ringRadius{ sinf(phi) * radius };

		for (int s = 0; s < columns; ++s)
		{
			float theta{ s * thetaStep };
			float x{ -sinf(theta) * ringRadius };
			float z{ cosf(theta) * ringRadius };
			const float u{ s * uStep };
			const float v{ 1.0f - (r * vStep) };

			const Vector3 position{ x, y, z };
			const Vector3 normal = Normalize(position);
			const Vector3 tangent = Normalize({ -normal.z, 0.0f, normal.x });
			const Vector2 texCoord{ u, v };

			mesh.vertices.push_back({ position, normal, tangent, texCoord });
		}
	}

	for (int r = 0; r + 1 < rows; ++r)
	{
		for (int c = 0; c + 1 < columns; ++c)
		{
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));

			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
		}
	}

	return mesh;
}
#pragma endregion

#pragma region CREATE PLANE
Mesh MeshBuilder::CreatePlane(float size, int rows, int columns)
{
	Mesh mesh;

	const float cellWidth = size / (columns - 1);
	const float cellHeight = size / (rows - 1);
	const float xOffset = size * -0.5f;
	const float zOffset = size * -0.5f;

	const float uStep{ 1.0f / columns };
	const float vStep{ 1.0f / (rows - 1.0f) };

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			float x{ (c * cellWidth) + xOffset };
			float y{ 0.0f };
			float z{ (r * cellHeight) + zOffset };

			const float u = uStep * c;
			const float v = vStep * r;

			mesh.vertices.push_back({ {x, y, z}, Vector3::YAxis, Vector3::XAxis, {u, v} });
		}
	}

	for (int r = 0; r + 1 < rows; ++r)
	{
		for (int c = 0; c + 1 < columns; ++c)
		{
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));

			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
		}
	}

	return mesh;
}
#pragma endregion

#pragma region CREATE PLANE TILE
Mesh MeshBuilder::CreatePlaneTile(float size, int rows, int columns, float tiling)
{
	Mesh mesh;

	const float cellWidth = size / (columns - 1);
	const float cellHeight = size / (rows - 1);
	const float xOffset = size * -0.5f;
	const float zOffset = size * -0.5f;

	const float uStep{ tiling / columns };
	const float vStep{ tiling / (rows - 1.0f) };

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			float x{ (c * cellWidth) + xOffset };
			float y{ 0.0f };
			float z{ (r * cellHeight) + zOffset };

			const float u = uStep * c;
			const float v = vStep * r;

			mesh.vertices.push_back({ {x, y, z}, Vector3::YAxis, Vector3::XAxis, {u, v} });
		}
	}

	for (int r = 0; r + 1 < rows; ++r)
	{
		for (int c = 0; c + 1 < columns; ++c)
		{
			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 0) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));

			mesh.indices.push_back((c + 0) + ((r + 0) * columns));
			mesh.indices.push_back((c + 1) + ((r + 1) * columns));
			mesh.indices.push_back((c + 1) + ((r + 0) * columns));
		}
	}

	return mesh;
}
#pragma endregion