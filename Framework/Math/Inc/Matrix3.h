#pragma once

namespace BOTE::Math
{
	struct Matrix3
	{
		union
		{
			struct 
			{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float v[9];
		};

		constexpr Matrix3()
			: _11(1.0f), _12(0.0f), _13(0.0f)
			, _21(0.0f), _22(1.0f), _23(0.0f)
			, _31(0.0f), _32(0.0f), _33(1.0f)
		{}

		constexpr Matrix3(
			float _11, float _12, float _13,
			float _21, float _22, float _23,
			float _31, float _32, float _33
		)
			: _11(_11), _12(_12), _13(_13)
			, _21(_21), _22(_22), _23(_23)
			, _31(_31), _32(_32), _33(_33)
		{}

#pragma region NEGATION
		Matrix3 operator-() const
		{
			return
			{
				-_11, -_12, -_13,
				-_21, -_22, -_23,
				-_31, -_32, -_33
			};
		}
#pragma endregion

#pragma region MATRIX ADDITION
		constexpr Matrix3 operator+(const Matrix3& m) const
		{
			return
			{
				_11 + m._11, _12 + m._12, _13 + m._13, // | 11, 12, 13 |
				_21 + m._21, _22 + m._22, _23 + m._23, // | 21, 22, 23 |
				_31 + m._31, _32 + m._32, _33 + m._33  // | 31, 32, 33 |
			};
		}
		
		constexpr Matrix3 operator+=(const Matrix3& m) const
		{
			return
			{
				_11 + m._11, _12 + m._12, _13 + m._13, // | 11, 12, 13 |
				_21 + m._21, _22 + m._22, _23 + m._23, // | 21, 22, 23 |
				_31 + m._31, _32 + m._32, _33 + m._33  // | 31, 32, 33 |
			};
		}
#pragma endregion

#pragma region MATRIX SUBSTRACION
		constexpr Matrix3 operator-(const Matrix3& m) const
		{
			return
			{
				_11 - m._11, _12 - m._12, _13 - m._13, // | 11, 12, 13 |
				_21 - m._21, _22 - m._22, _23 - m._23, // | 21, 22, 23 |
				_31 - m._31, _32 - m._32, _33 - m._33  // | 31, 32, 33 |
			};
		}
#pragma endregion

#pragma region MATRIX ADD EQUAL
		constexpr Matrix3 operator+=(const Matrix3& m)
		{
			// | 11, 12, 13 |
			_11 += m._11;
			_12 += m._12;
			_13 += m._13;

			// | 21, 22, 23 |
			_21 += m._21;
			_22 += m._22;
			_23 += m._23;

			// | 31, 32, 33 |
			_31 += m._31;
			_32 += m._32;
			_33 += m._33;

			return *this;
		}
#pragma endregion

#pragma region MATRIX SUB EQUAL
		constexpr Matrix3 operator-=(const Matrix3& m)
		{
			// | 11, 12, 13 |
			_11 -= m._11;
			_12 -= m._12;
			_13 -= m._13;

			// | 21, 22, 23 |
			_21 -= m._21;
			_22 -= m._22;
			_23 -= m._23;

			// | 31, 32, 33 |
			_31 -= m._31;
			_32 -= m._32;
			_33 -= m._33;

			return *this;
		}
#pragma endregion

#pragma region MATRIX MULTIPLICATION
#pragma region SCALAR
		// Scalar Matrix Multiplication
		constexpr Matrix3 operator*(float& s) const
		{
			return
			{
				_11 * s, _12 * s, _13 * s,
				_21 * s, _22 * s, _23 * s,
				_31 * s, _32 * s, _33 * s
			};
		}

		constexpr Matrix3 operator*=(float& s) const
		{
			return
			{
				_11 * s, _12 * s, _13 * s,
				_21 * s, _22 * s, _23 * s,
				_31 * s, _32 * s, _33 * s
			};
		}
#pragma endregion

#pragma region MATRIX * MATRIX
		// Matrix Multiplication
		constexpr Matrix3 operator*(const Matrix3& m)
		{
			return
			{
				(_11 * m._11) + (_12 * m._21) + (_13 * m._31), // 11
				(_11 * m._12) + (_12 * m._22) + (_13 * m._32), // 12
				(_11 * m._13) + (_12 * m._23) + (_13 * m._33), // 13

				(_21 * m._11) + (_22 * m._21) + (_23 * m._31), // 21
				(_21 * m._12) + (_22 * m._22) + (_23 * m._32), // 22
				(_21 * m._13) + (_22 * m._23) + (_23 * m._33), // 23

				(_31 * m._11) + (_32 * m._21) + (_33 * m._31), // 31
				(_31 * m._12) + (_32 * m._22) + (_33 * m._32), // 32
				(_31 * m._13) + (_32 * m._23) + (_33 * m._33)  // 33
			};
		}

		constexpr Matrix3 operator*=(const Matrix3& m)
		{
			return
			{
				(_11 * m._11) + (_12 * m._21) + (_13 * m._31), // 11
				(_11 * m._12) + (_12 * m._22) + (_13 * m._32), // 12
				(_11 * m._13) + (_12 * m._23) + (_13 * m._33), // 13

				(_21 * m._11) + (_22 * m._21) + (_23 * m._31), // 21
				(_21 * m._12) + (_22 * m._22) + (_23 * m._32), // 22
				(_21 * m._13) + (_22 * m._23) + (_23 * m._33), // 23

				(_31 * m._11) + (_32 * m._21) + (_33 * m._31), // 31
				(_31 * m._12) + (_32 * m._22) + (_33 * m._32), // 32
				(_31 * m._13) + (_32 * m._23) + (_33 * m._33)  // 33
			};
		}
#pragma endregion
#pragma endregion

#pragma region MATRIX IDENTITY
		static Matrix3 Identity()
		{
			// Matrix 3				// Matrix Identity
			// | 11, 12, 13 |		// | 1, 0, 0 |
			// | 21, 22, 23 |		// | 0, 1, 0 |
			// | 31, 32, 33 |		// | 0, 0, 1 |

			return
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
		}
#pragma endregion

#pragma region ROTATION
		static Matrix3 Rotation(const float& rad)
		{
			// ROTATION ABOUT ORIGIN
			// |  cos(-), sin(-), 0 |
			// | -sin(-), cos(-), 0 |
			// |    0   ,   0   , 1 |

			return
			{
				cosf(rad) , sinf(rad), 0.0f,
				-sinf(rad), cosf(rad), 0.0f,
				   0.0f   ,   0.0f   , 1.0f
			};
		}
#pragma endregion

#pragma region SCALING
		static Matrix3 Scaling(const Vector2& s)
		{
			// Scale about Origin
			// | W, 0, 0 |
			// | 0, H, 0 |
			// | 0, 0, 1 |

			return
			{
				s.x, 0.0f, 0.0f,
				0.0f, s.y, 0.0f,
				0.0f, 0.0f, 1.0f
			};
		}

		static Matrix3 Scaling(const float& sx, const float& sy)
		{
			return
			{
				sx, 0.0f, 0.0f,
				0.0f, sy, 0.0f,
				0.0f, 0.0f, 1.0f
			};
		}
#pragma endregion

#pragma region TRANSLATION
		static Matrix3 Translation(const Vector2& d)
		{
			return
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				d.x , d.y , 1.0f
			};
		}

		static Matrix3 Translation(const float& dx, const float& dy)
		{
			return
			{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				 dx ,  dy , 1.0f
			};
		}
#pragma endregion
	};
}