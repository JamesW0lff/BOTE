#pragma once

#include "Colors.h"

namespace BOTE::Graphics
{
	struct Material
	{
	public:
		void MDebugUI();

	public: 
		Color ambient = Colors::White; // rgba = 4 floats = 16 bytes
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		Color emissive = Colors::Black;
		
		float power =  1.0f;
		float padding[3] = { 0.0f }; // Memory padding to keep struct 16 byte aligned for VRAM
	};
}