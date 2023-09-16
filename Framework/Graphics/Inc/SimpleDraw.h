#pragma once

#include "Colors.h"

namespace BOTE::Graphics
{
	class Camera;
}

namespace BOTE::Graphics::SimpleDraw
{
	void StaticInitialize(uint32_t maxVertexCount = 10000);
	void StaticTerminate();

	void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, Color color);
	void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, Color color);
	// Axis Align Bounding Box
	void AddAABB(const Math::Vector3& min, const Math::Vector3& max, Color color);
	void AddSphere(const Math::Vector3& center, float radius, Color color);
	void AddTransform(const Math::Matrix4& transform);
	// When you have a 4x4 matrix
	// 	   Top 3x3 are the orientation
	// [ rx ry rz 0 ] Where (rx ry rz) is your right vector (X::Red)
	// [ ux uy uz 0 ] where (ux uy uz) is your up vector (Y::Green)
	// [ lx ly lz 0 ] where (lx ly lz) is yout look vector (Z::Blue)
	// [ px py pz 1 ] where (px py pz) is your position
	void AddPlane(float size, const Color& color = Colors::DarkGray);
	// for(...) DrawLine -x to x
	// for(...) DrawLine -z to z

	// For challenge, you can add also:
	// - AddCylinder
	// - AddCone
	// - AddCapsule

	void Render(const Camera& camera);
}