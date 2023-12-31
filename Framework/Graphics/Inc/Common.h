#pragma once

// Engine headers
#include <Core/Inc/Core.h>
#include <Math/Inc/EngineMath.h>

// DirectX headers
#include <d3d11_1.h>
#include <d3dcompiler.h>

// External headers
#include <ImGui/Inc/imgui.h>

// DirectX libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

// Utility function to release DirectX interfaces
template <class T>
inline void SafeRelease(T*& p)
{
	if (p)
	{
		p->Release();
		p = nullptr;
	}
}