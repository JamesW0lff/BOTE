#pragma once

namespace BOTE::Graphics
{
	class PixelShader
	{
	public:
		void Initialize(LPCWSTR fileName, const char* entryPoint = "PS"); // LPCWSTR = Long Pointer to Constant Wide String
		void Terminate();
		void Bind() const;

	private:
		ID3D11PixelShader* mPixelShader = nullptr;
	};
};