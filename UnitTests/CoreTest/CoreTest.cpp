#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BOTE::Core;

namespace CoreTest
{
	TEST_CLASS(BlockAllocatorTest)
	{
	public:
		
		TEST_METHOD(OneBlockTest)
		{
			BlockAllocator blockAllocator(16, 1);

		}
	};
}
