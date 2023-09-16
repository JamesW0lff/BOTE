#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BOTE::Math;

namespace MathTest
{
	TEST_CLASS(Matrix3Test)
	{
	public:
#pragma region TEST CONSTRUCTOR
		TEST_METHOD(TestConstructor)
		{
			Matrix3 m;

			Assert::AreEqual(m._11, 1.0f);
			Assert::AreEqual(m._12, 0.0f);
			Assert::AreEqual(m._13, 0.0f);

			Assert::AreEqual(m._21, 0.0f);
			Assert::AreEqual(m._22, 1.0f);
			Assert::AreEqual(m._23, 0.0f);

			Assert::AreEqual(m._31, 0.0f);
			Assert::AreEqual(m._32, 0.0f);
			Assert::AreEqual(m._33, 1.0f);

			Matrix3 m2 =
			{
				1.5f, 2.0f, -6.5f,
				0.0f, -1.0f, 2.5f,
				-2.6f, -4.5f, -0.344f
			};

			Assert::AreEqual(m2._11, 1.5f);
			Assert::AreEqual(m2._12, 2.0f);
			Assert::AreEqual(m2._13, -6.5f);

			Assert::AreEqual(m2._21, 0.0f);
			Assert::AreEqual(m2._22, -1.0f);
			Assert::AreEqual(m2._23, 2.5f);

			Assert::AreEqual(m2._31, -2.6f);
			Assert::AreEqual(m2._32, -4.5f);
			Assert::AreEqual(m2._33, -0.344f);

		}
#pragma endregion

#pragma region TEST NEGATION
		TEST_METHOD(TestNegation)
		{
			Matrix3 m =
			{
				1.0f, 2.0f, 3.0f,
				-0.4f, -0.5f, -0.6f,
				7.0f, -0.8f, -9.0f
			};

			m = -m;

			Assert::AreEqual(m._11, -1.0f);
			Assert::AreEqual(m._12, -2.0f);
			Assert::AreEqual(m._13, -3.0f);

			Assert::AreEqual(m._21, 0.4f);
			Assert::AreEqual(m._22, 0.5f);
			Assert::AreEqual(m._23, 0.6f);

			Assert::AreEqual(m._31, -7.0f);
			Assert::AreEqual(m._32, 0.8f);
			Assert::AreEqual(m._33, 9.0f);
		}
#pragma endregion

#pragma region TEST ADDITION
		TEST_METHOD(TestAddition)
		{
			Matrix3 m1 =
			{
				1.0f, 2.0f, 3.0f,
				4.0f, -5.0f, 6.5f,
				-0.7f, 8.9f, 10.0f
			};

			Matrix3 m2 =
			{
				-0.7f, 8.9f, 10.0f,
				4.0f, -5.0f, 6.5f,
				1.0f, 2.0f, 3.0f
			};

			Matrix3 res = m1 + m2;

			Assert::AreEqual(res._11, 0.3f);
			Assert::AreEqual(res._12, 10.9f);
			Assert::AreEqual(res._13, 13.0f);
			
			Assert::AreEqual(res._21, 8.0f);
			Assert::AreEqual(res._22, -10.0f);
			Assert::AreEqual(res._23, 13.0f);

			Assert::AreEqual(res._31, 0.3f);
			Assert::AreEqual(res._32, 10.9f);
			Assert::AreEqual(res._33, 13.0f);
		}
#pragma endregion

#pragma region TEST SUBSTRACTION
		TEST_METHOD(TestSubstaction)
		{
			Matrix3 m0 =
			{
				1.0f, 2.0f, 3.0f,
				-0.4f, -0.5f, -0.6f,
				7.0f, -0.8f, -9.0f
			};

			Matrix3 m1 =
			{
				-1.0f, 2.0f, -3.0f,
				0.4f, -0.5f, 0.6f,
				7.0f, -0.8f, 9.0f
			};

			Matrix3 sub = m0 - m1;

			Assert::AreEqual(sub._11, 2.0f, 0.001f);
			Assert::AreEqual(sub._12, 0.0f, 0.001f);
			Assert::AreEqual(sub._13, 6.0f, 0.001f);

			Assert::AreEqual(sub._21, -0.8f, 0.001f);
			Assert::AreEqual(sub._22, 0.0f, 0.001f);
			Assert::AreEqual(sub._23, -1.2f, 0.001f);

			Assert::AreEqual(sub._31, 0.0f, 0.001f);
			Assert::AreEqual(sub._32, 0.0f, 0.001f);
			Assert::AreEqual(sub._33, -18.0f, 0.001f);
		}
#pragma endregion

#pragma region TEST ADD EQUAL
		TEST_METHOD(TestAddEqual)
		{
			Matrix3 m =
			{
				1.0f, 2.0f, 3.0f,
				-1.0f, -2.0f, -3.0f,
				1.5f, -2.4f, -3.3f
			};

			Matrix3 m2 = 
			{
			1.0f, 0.2f, -3.3f,
			2.2f, 1.0f, 3.0f,
			1.5f, 0.5f, -0.3f
			};

			m += m2;
			
			// AreEqual(<result>, <expected>, <tolerance>);
			Assert::AreEqual(m._11, 2.0f);
			Assert::AreEqual(m._12, 2.2f);
			Assert::AreEqual(m._13, -0.3f, 0.01f);

			Assert::AreEqual(m._21, 1.2f);
			Assert::AreEqual(m._22, -1.0f);
			Assert::AreEqual(m._23, 0.0f);

			Assert::AreEqual(m._31, 3.0f);
			Assert::AreEqual(m._32, -1.9f, 0.01f);
			Assert::AreEqual(m._33, -3.6f);
		}
#pragma endregion

#pragma region TEST SUB EQUAL
		TEST_METHOD(TestSubEqual)
		{
			Matrix3 m1 =
			{
				1.0f, 2.0f, 3.0f,
				4.0f, -5.0f, 6.5f,
				-0.7f, 8.9f, 10.0f
			};

			Matrix3 m2 =
			{
				-0.7f, 8.9f, 10.0f,
				4.0f, -5.0f, 6.5f,
				1.0f, 2.0f, 3.0f
			};

			m1 -= m2;

			Assert::AreEqual(m1._11, 1.7f, 0.001f);
			Assert::AreEqual(m1._12, -6.9f, 0.001f);
			Assert::AreEqual(m1._13, -7.0f, 0.001f);

			Assert::AreEqual(m1._21, 0.0f, 0.001f);
			Assert::AreEqual(m1._22, 0.0f, 0.001f);
			Assert::AreEqual(m1._23, 0.0f, 0.001f);

			Assert::AreEqual(m1._31, -1.7f, 0.001f);
			Assert::AreEqual(m1._32, 6.9f, 0.001f);
			Assert::AreEqual(m1._33, 7.0f, 0.001f);
		}
#pragma endregion

	};
}