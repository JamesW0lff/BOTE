#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BOTE::Math;

namespace MathTest
{
	TEST_CLASS(Vector3Test)
	{
	public:
		
#pragma region TEST CONSTRUCTOR
		TEST_METHOD(TestConstructor)
		{
			Vector3 v0;
			Assert::AreEqual(v0.x, 0.0f);
			Assert::AreEqual(v0.y, 0.0f);
			Assert::AreEqual(v0.z, 0.0f);

			Vector3 v1(1.0f);
			Assert::AreEqual(v1.x, 1.0f);
			Assert::AreEqual(v1.y, 1.0f);
			Assert::AreEqual(v1.z, 1.0f);

			Vector3 v2(1.0f, 2.0f, 3.0f);
			Assert::AreEqual(v2.x, 1.0f);
			Assert::AreEqual(v2.y, 2.0f);
			Assert::AreEqual(v2.z, 3.0f);
		}
#pragma endregion

#pragma region TEST STATICS
		TEST_METHOD(TestStatics)
		{
			Vector3 zero = Vector3::Zero;
			Assert::AreEqual(zero.x, 0.0f);
			Assert::AreEqual(zero.y, 0.0f);
			Assert::AreEqual(zero.z, 0.0f);

			Vector3 one = Vector3::One;
			Assert::AreEqual(one.x, 1.0f);
			Assert::AreEqual(one.y, 1.0f);
			Assert::AreEqual(one.z, 1.0f);

			Vector3 xAxis = Vector3::XAxis;
			Assert::AreEqual(xAxis.x, 1.0f);
			Assert::AreEqual(xAxis.y, 0.0f);
			Assert::AreEqual(xAxis.z, 0.0f);

			Vector3 yAxis = Vector3::YAxis;
			Assert::AreEqual(yAxis.x, 0.0f);
			Assert::AreEqual(yAxis.y, 1.0f);
			Assert::AreEqual(yAxis.z, 0.0f);

			Vector3 zAxis = Vector3::ZAxis;
			Assert::AreEqual(zAxis.x, 0.0f);
			Assert::AreEqual(zAxis.y, 0.0f);
			Assert::AreEqual(zAxis.z, 1.0f);
		}
#pragma endregion

#pragma region TEST NEGATION
		TEST_METHOD(TestNegation)
		{
			Vector3 v(2.0f, 3.0f, 4.0f);
			Vector3 negV = -v;
			Assert::AreEqual(negV.x, -2.0f);
			Assert::AreEqual(negV.y, -3.0f);
			Assert::AreEqual(negV.z, -4.0f);
		}
#pragma endregion

#pragma region TEST ADDITION
		TEST_METHOD(TestAddition)
		{
			Vector3 v0(1.0f);
			Vector3 v1(2.0f, 3.0f, 4.0f);
			Vector3 v2 = v0 + v1;
			Assert::AreEqual(v2.x, 3.0f);
			Assert::AreEqual(v2.y, 4.0f);
			Assert::AreEqual(v2.z, 5.0f);
		}
#pragma endregion

#pragma region TEST SUBTRACTION
		TEST_METHOD(TestSubtraction)
		{
			Vector3 v0(1.0f);
			Vector3 v1(2.0f, 3.0f, 4.0f);
			Vector3 v2 = v0 - v1;
			Assert::AreEqual(v2.x, -1.0f);
			Assert::AreEqual(v2.y, -2.0f);
			Assert::AreEqual(v2.z, -3.0f);
		}
#pragma endregion

#pragma region TEST MULTIPLY
		TEST_METHOD(TestMultiply)
		{
			Vector3 v0(2.0f, 3.0f, 4.0f);
			Vector3 v1 = v0 * 3.0f;
			Assert::AreEqual(v1.x, 6.0f);
			Assert::AreEqual(v1.y, 9.0f);
			Assert::AreEqual(v1.z, 12.0f);
		}
#pragma endregion

#pragma region TEST ADD EQUAL
		TEST_METHOD(TestAddEqual)
		{
			Vector3 v(2.0f, 3.0f, 4.0f);
			v += { 0.5f, 0.4f, 0.3f };
			Assert::AreEqual(v.x, 2.5f);
			Assert::AreEqual(v.y, 3.4f);
			Assert::AreEqual(v.z, 4.3f);
		}
#pragma endregion

#pragma region TEST SUBSTRACTION EQUAL
		TEST_METHOD(TestSubtractEqual)
		{
			Vector3 v(2.0f, 3.0f, 4.0f);
			v -= { 0.5f, 0.4f, 0.3f };
			Assert::AreEqual(v.x, 1.5f);
			Assert::AreEqual(v.y, 2.6f);
			Assert::AreEqual(v.z, 3.7f);
		}
#pragma endregion

#pragma region TEST MULTIPLY EQUAL
		TEST_METHOD(TestMultiplyEqual)
		{
			Vector3 v(2.0f, 3.0f, 4.0f);
			v *= 2.0f;
			Assert::AreEqual(v.x, 4.0f);
			Assert::AreEqual(v.y, 6.0f);
			Assert::AreEqual(v.z, 8.0f);
		}
#pragma endregion

#pragma region TEST DIVIDE
		TEST_METHOD(TestDivide)
		{
			Vector3 v(2.0f, 3.0f, 4.0f);
			v /= 2.0f;
			Assert::AreEqual(v.x, 1.0f);
			Assert::AreEqual(v.y, 1.5f);
			Assert::AreEqual(v.z, 2.0f);
		}
#pragma endregion

};
}
