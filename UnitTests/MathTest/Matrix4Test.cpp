#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BOTE::Math;

namespace MathTest
{
	TEST_CLASS(Matrix4Test)
	{
	public:
#pragma region TEST CONSTRUCTOR
		TEST_METHOD(TestConstructor)
		{
			Matrix4 m;

			Assert::AreEqual(m._11, 1.0f);
			Assert::AreEqual(m._12, 0.0f);
			Assert::AreEqual(m._13, 0.0f);
			Assert::AreEqual(m._14, 0.0f);

			Assert::AreEqual(m._21, 0.0f);
			Assert::AreEqual(m._22, 1.0f);
			Assert::AreEqual(m._23, 0.0f);
			Assert::AreEqual(m._24, 0.0f);

			Assert::AreEqual(m._31, 0.0f);
			Assert::AreEqual(m._32, 0.0f);
			Assert::AreEqual(m._33, 1.0f);
			Assert::AreEqual(m._34, 0.0f);
			
			Assert::AreEqual(m._41, 0.0f);
			Assert::AreEqual(m._42, 0.0f);
			Assert::AreEqual(m._43, 0.0f);
			Assert::AreEqual(m._44, 1.0f);

		}

	};
}