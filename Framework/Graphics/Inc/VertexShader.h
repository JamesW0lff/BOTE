#pragma once

namespace BOTE::Graphics
{
	class VertexShader
	{
	public:
		void Initialize(LPCWSTR fileName, uint32_t vertexFormat);
		void Terminate();
		void Bind() const;

	private:
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;
	};
}