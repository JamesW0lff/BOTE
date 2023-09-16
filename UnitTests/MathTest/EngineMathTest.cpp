#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BOTE::Math;

namespace MathTest
{
	TEST_CLASS(EngineMathTest)
	{
	public:
#pragma region VECTOR 2 METHODS
#pragma region DOT
		TEST_METHOD(Dot2D)
		{
			Vector2 v0 = { 1.0f, 2.0f };
			Vector2 v1 = { 1.0f, 3.5f };
			
			float dotTest = BOTE::Math::Dot(v0, v1);

			Assert::AreEqual(dotTest, 8.0f);
		}
#pragma endregion

#pragma region MAGNITUDE
		TEST_METHOD(Magnitude2D)
		{
			Vector2 v = { 2.5f, -2.0f };

			float magnitude = BOTE::Math::Magnitude(v);
			Assert::AreEqual(magnitude, 3.201562119f);
		}
#pragma endregion

#pragma region DISTANCE
		TEST_METHOD(Distance2D)
		{
			Vector2 v0 = { 1.0f, -2.5f };
			Vector2 v1 = { -4.5f, 3.5f };

			float distance = BOTE::Math::Distance(v0, v1);

			Assert::AreEqual(distance, 8.139410298f);

		}
#pragma endregion

#pragma region NORMAL
		TEST_METHOD(Normalize2D)
		{
			Vector2 v = { 2.5f, -2.0f };

			Vector2 normal = BOTE::Math::Normalize(v);

			Assert::AreEqual(normal.x, 0.780868769f);
			Assert::AreEqual(normal.y,-0.624695063f);
		}
#pragma endregion

#pragma region CROSS
		TEST_METHOD(Cross2D)
		{
			Vector2 v0 = { 1.0f, 2.0f };
			Vector2 v1 = { 1.0f, 3.5f };

			float cross = BOTE::Math::Cross(v0, v1);

			Assert::AreEqual(cross, 1.5f);
		}
#pragma endregion
#pragma endregion

#pragma region VECTOR 3 METHODS
#pragma region DOT
		TEST_METHOD(Dot3D)
		{
			Vector3 v0 = { 1.0f, 2.0f, -3.5f };
			Vector3 v1 = { 1.0f, 3.5f, -5.5f };

			float dotTest = BOTE::Math::Dot(v0, v1);

			Assert::AreEqual(dotTest, 27.25f);
		}
#pragma endregion

#pragma region MAGNITUDE
		TEST_METHOD(Magnitude3D)
		{
			Vector3 v = { 2.5f, 3.2f, -2.0f };
			
			float magnitude = BOTE::Math::Magnitude(v);
			Assert::AreEqual(magnitude, 4.52658844f);
		}
#pragma endregion

#pragma region LERP
		TEST_METHOD(LERP)
		{
			Vector3 v0 = { 1.0f, 2.0f, 3.0f };
			Vector3 v1 = { 3.0f, -2.0f, 1.5f };
			float t = 10.0f;

			Vector3 lerp = BOTE::Math::Lerp(v0, v1, t);

			// v1 * t = {30.0f, -20.0f, 15.0f}
			// 1.0f - 10.0f = -9.0f
			// v0 * -9.0f = {-9.0f, -18.0f, -27.0f}
			// {21.0f, -38.0f, -12.0f}
			Assert::AreEqual(lerp.x, 21.0f);
			Assert::AreEqual(lerp.y, -38.0f);
			Assert::AreEqual(lerp.z, -12.0f);

		}
#pragma endregion
#pragma endregion
	};
}