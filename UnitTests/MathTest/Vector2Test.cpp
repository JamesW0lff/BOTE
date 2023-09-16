#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BOTE::Math;

namespace MathTest
{
	TEST_CLASS(Vector2Test)
	{
	public:

#pragma region TEST CONSTRUCTOR
		TEST_METHOD(TestConstructor)
		{
			Vector2 v0;
			Assert::AreEqual(v0.x, 0.0f);
			Assert::AreEqual(v0.y, 0.0f);

			Vector2 v1(1.0f);
			Assert::AreEqual(v1.x, 1.0f);
			Assert::AreEqual(v1.y, 1.0f);

			Vector2 v2(1.0f, 2.0f);
			Assert::AreEqual(v2.x, 1.0f);
			Assert::AreEqual(v2.y, 2.0f);
		}
#pragma endregion

#pragma region TEST STATICS
		TEST_METHOD(TestStatics)
		{
			Vector2 zero = Vector2::Zero;
			Assert::AreEqual(zero.x, 0.0f);
			Assert::AreEqual(zero.y, 0.0f);

			Vector2 one = Vector2::One;
			Assert::AreEqual(one.x, 1.0f);
			Assert::AreEqual(one.y, 1.0f);

			Vector2 xAxis = Vector2::XAxis;
			Assert::AreEqual(xAxis.x, 1.0f);
			Assert::AreEqual(xAxis.y, 0.0f);

			Vector2 yAxis = Vector2::YAxis;
			Assert::AreEqual(yAxis.x, 0.0f);
			Assert::AreEqual(yAxis.y, 1.0f);
		}
#pragma endregion

#pragma region TEST NEGATION
		TEST_METHOD(TestNegation)
		{
			Vector2 v(2.0f, 3.0f);
			Vector2 negV = -v;
			Assert::AreEqual(negV.x, -2.0f);
			Assert::AreEqual(negV.y, -3.0f);
		}
#pragma endregion

#pragma region TEST ADDITION
		TEST_METHOD(TestAddition)
		{
			Vector2 v0(1.0f);
			Vector2 v1(2.0f, 3.0f);
			Vector2 v2 = v0 + v1;
			Assert::AreEqual(v2.x, 3.0f);
			Assert::AreEqual(v2.y, 4.0f);
		}
#pragma endregion

#pragma region TEST SUBTRACTION
		TEST_METHOD(TestSubtraction)
		{
			Vector2 v0(1.0f);
			Vector2 v1(2.0f, 3.0f);
			Vector2 v2 = v0 - v1;
			Assert::AreEqual(v2.x, -1.0f);
			Assert::AreEqual(v2.y, -2.0f);
		}
#pragma endregion

#pragma region TEST MULTIPLY
		TEST_METHOD(TestMultiply)
		{
			Vector2 v0(2.0f, 3.0f);
			Vector2 v1 = v0 * 3.0f;
			Assert::AreEqual(v1.x, 6.0f);
			Assert::AreEqual(v1.y, 9.0f);
		}
#pragma endregion

#pragma region TEST ADD EQUAL
		TEST_METHOD(TestAddEqual)
		{
			Vector2 v(2.0f, 3.0f);
			v += { 0.5f, 0.4f};
			Assert::AreEqual(v.x, 2.5f);
			Assert::AreEqual(v.y, 3.4f);
		}
#pragma endregion

#pragma region TEST SUBSTRACTION EQUAL
		TEST_METHOD(TestSubtractEqual)
		{
			Vector2 v(2.0f, 3.0f);
			v -= { 0.5f, 0.4f};
			Assert::AreEqual(v.x, 1.5f);
			Assert::AreEqual(v.y, 2.6f);
		}
#pragma endregion

#pragma region TEST MULTIPLY EQUAL
		TEST_METHOD(TestMultiplyEqual)
		{
			Vector2 v(2.0f, 3.0f);
			v *= 2.0f;
			Assert::AreEqual(v.x, 4.0f);
			Assert::AreEqual(v.y, 6.0f);
		}
#pragma endregion

#pragma region TEST DIVIDE
		TEST_METHOD(TestDivide)
		{
			Vector2 v(2.0f, 3.0f);
			v /= 2.0f;
			Assert::AreEqual(v.x, 1.0f);
			Assert::AreEqual(v.y, 1.5f);
		}
#pragma endregion

	};
}
