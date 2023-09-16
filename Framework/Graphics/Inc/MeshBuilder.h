#pragma once

#include "MeshTypes.h"

namespace BOTE::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPC CreateCubePC(Color color);
		static MeshPC CreatePlanePC(float size, int rows = 16, int columns = 16, Color color = Colors::White);
		static MeshPC CreateCylinderPC(float height, float radius, int rings = 16, int slices = 16, Color color = Colors::White);
		static MeshPC CreateSpherePC(float radius, int rings = 16, int slices = 16, Color color = Colors::White);
		
		static MeshPX CreateSpherePX(float radius, int rings = 16, int slices = 16);
		static MeshPX CreateSkydomePX(float radius, int rings = 16, int slices = 16);
		static MeshPX CreateNDCQuad();
		
		static Mesh CreateSphere(float radius, int rings = 16, int slices = 16);
		static Mesh CreatePlane(float size, int rows = 16, int columns = 16);
		static Mesh CreatePlaneTile(float size, int rows = 16, int columns = 16, float tiling = 1.0f);
	};
}
