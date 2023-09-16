#pragma once

#include "Colors.h"

namespace BOTE::Graphics
{
	class DirectionalLight
	{
	public:
		void DebugUI();

	public:
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		Math::Vector3 direction = -Math::Vector3::YAxis;
		float padding = 0.0f;
	};
}