#include "Precompiled.h"
#include "TextureManager.h"

using namespace BOTE;
using namespace BOTE::Graphics;

namespace
{
	std::unique_ptr<TextureManager> sInstance;
}

void TextureManager::StaticInitialize()
{
	ASSERT(sInstance == nullptr, "TextureManager -- Manager already initialized.");
	sInstance == std::make_unique<TextureManager>();
}

void TextureManager::StaticTerminate()
{
	sInstance.reset();
}

TextureManager* TextureManager::Get()
{
	ASSERT(sInstance != nullptr, "TextureManager -- Manager not initialized.");
	return sInstance.get();
}

TextureManager::~TextureManager()
{
	for (auto& [id, texture] : mInventory)
		texture->Terminate();
	mInventory.clear();
}

TextureID TextureManager::LoadTexture(std::filesystem::path fileName)
{
	const auto textureID = std::filesystem::hash_value(fileName);
	const auto [iter, success] = mInventory.insert({ textureID, nullptr });
	if (success)
	{
		auto& texturePtr = iter->second;
		texturePtr = std::make_unique<Texture>();
		texturePtr->Initialize(fileName);
	}
	return textureID;
}

const Texture* TextureManager::GetTexture(TextureID id) const
{
	const auto iter = mInventory.find(id);
	if (iter == mInventory.end())
		return nullptr;
	return iter->second.get();
}

void TextureManager::BindVS(TextureID id, uint32_t slotIndex)
{
	const auto texture = GetTexture(id);
	if (texture)
		texture->BindVS(slotIndex);
}

void TextureManager::BindPS(TextureID id, uint32_t slotIndex)
{
	const auto texture = GetTexture(id);
	if (texture)
		texture->BindPS(slotIndex);
}