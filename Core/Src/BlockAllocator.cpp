#include "Precompiled.h"

#include "BlockAllocator.h"
#include "DebugUtil.h"

using namespace BOTE::Core;

BlockAllocator::BlockAllocator(size_t blockSize, size_t capacity)
	: mData(nullptr)
	, mBlockSize(blockSize)
	, mCapacity(capacity)
{
	// Do one malloc to allocate all the memory needed
	// Create free block pointers
}

BlockAllocator::~BlockAllocator()
{
	// do one free to release all allocated memory
	free(mData);
}

void* BlockAllocator::Allocate()
{
	// Return a free block, or a nullptr if all blocks are occupied
	return nullptr;
}

void BlockAllocator::Free(void* ptr)
{
	// Valid ptr, and collect into free blocks
}