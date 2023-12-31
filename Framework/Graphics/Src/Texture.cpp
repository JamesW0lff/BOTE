#include "Precompiled.h"
#include "Texture.h"

#include "GraphicsSystem.h"
#include <DirectXTK/Inc/WICTextureLoader.h>

using namespace BOTE::Graphics;

#pragma region UNBIND PS
void Texture::UnbindPS(uint32_t slot)
{
	static ID3D11ShaderResourceView* dummy = nullptr;
	auto context = GraphicsSystem::Get()->GetContext();
	context->PSSetShaderResources(slot, 1, &dummy);
}
#pragma endregion

Texture::~Texture()
{
	ASSERT(mShaderResourceView == nullptr, "Texture -- Terminate must be called before destruction.");
}

#pragma region INITIALIZE
void Texture::Initialize(const std::filesystem::path& fileName)
{
	auto device = GraphicsSystem::Get()->GetDevice();
	auto context = GraphicsSystem::Get()->GetContext();

	// Load the texture
	HRESULT hr = DirectX::CreateWICTextureFromFile(device, context, fileName.c_str(), nullptr, &mShaderResourceView);
	ASSERT(SUCCEEDED(hr), "Texture -- Failed to load texture %ls.", fileName.c_str());

	// Cache the texture dimensions
	ID3D11Resource* resource = nullptr;
	mShaderResourceView->GetResource(&resource);

	// Ask for the description of the texture before loading it
	ID3D11Texture2D* texture = static_cast<ID3D11Texture2D*>(resource);
	D3D11_TEXTURE2D_DESC desc = {};
	texture->GetDesc(&desc);

	mWidth = desc.Width;
	mHeight = desc.Height;
}
#pragma endregion

void Texture::Initialize(uint32_t width, uint32_t height, Format format)
{
	ASSERT(false, "Texture -- Not implemented.");
}

#pragma region TERMINATE
void Texture::Terminate()
{
	SafeRelease(mShaderResourceView);
}
#pragma endregion

#pragma region BIND VS
void Texture::BindVS(uint32_t slot) const
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->VSSetShaderResources(slot, 1, &mShaderResourceView);
}
#pragma endregion

#pragma region BIND PS
void Texture::BindPS(uint32_t slot) const
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->PSSetShaderResources(slot, 1, &mShaderResourceView);
}
#pragma endregion

#pragma region GET DXGI FORMAT
DXGI_FORMAT Texture::GetDXGIFormat(Format format)
{
	switch (format)
	{
	case Texture::Format::RGBA_U8:	return DXGI_FORMAT_R8G8B8A8_UNORM;
	case Texture::Format::RGBA_U32:	return DXGI_FORMAT_R32G32B32A32_UINT;
	default:
		ASSERT(false, "Texture -- Unsupported format %d.", static_cast<uint32_t>(format));
		break;
	}
	return DXGI_FORMAT_R8G8B8A8_UNORM;
};
#pragma endregion