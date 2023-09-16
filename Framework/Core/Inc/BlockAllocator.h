#pragma once

namespace BOTE::Core
{
	class BlockAllocator
	{
	public:
		BlockAllocator(size_t blockSize, size_t capacity);
		~BlockAllocator();

		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;
		
		BlockAllocator(BlockAllocator&&) = delete;
		BlockAllocator& operator=(BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);

	private:
		std::vector<void*> mFreeBlocks;
		void* mData = nullptr;
		size_t mBlockSize = 0;
		size_t mCapacity = 0;
	};
}