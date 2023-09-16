#pragma once

#include "Texture.h"

namespace BOTE::Graphics
{
	using TextureID = std::size_t;
	
	class TextureManager final
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static TextureManager* Get();

	public:
		~TextureManager();

		TextureID LoadTexture(std::filesystem::path fileName);

		const Texture* GetTexture(TextureID id) const;

		void BindVS(TextureID id, uint32_t slotIndex);
		void BindPS(TextureID id, uint32_t slotIndex);

	private:
		std::unordered_map<TextureID, std::unique_ptr<Texture>> mInventory;
	};
}