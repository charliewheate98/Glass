#pragma once

#include "pch.h"
#include <iostream>

namespace Glass
{
	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;

		Vector4(float xc, float yc, float zc, float wc = 0.f) :
			x(xc),
			y(yc),
			z(zc),
			w(wc)
		{}
		
		~Vector4()
		{}

		Vector4 operator *=(float s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return (*this);
		}

		Vector4 operator /=(float s)
		{
			s = 1.0f / s;
			x /= s;
			y /= s;
			z /= s;
			w /= s;
			return (*this);
		}

		inline float Magnitude(const Vector4& v)
		{
			return (std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
		}
	
		inline Vector4 Normalise(const Vector4& v)
		{
			return (Vector4(v.x / Magnitude(v), v.y / Magnitude(v), v.z / Magnitude(v), v.w / Magnitude(v)));
		}
	};

	inline Vector4 operator +(const Vector4& a, const Vector4& b)
	{
		return (Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
	}

	inline Vector4 operator -(const Vector4& a, const Vector4& b)
	{
		return (Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
	}

	struct Matrix4
	{
		float n[4][4];

		Matrix4() = default;

		Matrix4(Vector4& a, Vector4& b, Vector4& c, Vector4& d)
		{
			n[0][0] = a.x;  n[0][1] = a.y;  n[0][2] = a.z;  n[0][3] = a.w;
			n[1][0] = b.x;  n[1][1] = b.y;  n[1][2] = b.z;  n[1][3] = b.w;
			n[2][0] = c.x;  n[2][1] = c.y;  n[2][2] = c.z;  n[2][3] = c.w;
			n[3][0] = d.x;  n[3][1] = d.y;  n[3][2] = d.z;  n[3][3] = d.w;
		}

		Matrix4(float n00, float n01, float n02, float n03,
				float n10, float n11, float n12, float n13,
				float n20, float n21, float n22, float n23,
				float n30, float n31, float n32, float n33)
		{
			n[0][0] = n00; n[1][0] = n10; n[2][0] = n20; n[3][0] = n30;
			n[0][1] = n01; n[1][1] = n11; n[2][1] = n21; n[3][1] = n31;
			n[0][2] = n02; n[1][2] = n12; n[2][2] = n22; n[3][2] = n32;
			n[0][3] = n03; n[1][3] = n13; n[2][3] = n23; n[3][3] = n33;
		}

		float& operator ()(int i, int j)
		{
			return (n[i][j]);
		}
		 
		const float& operator ()(int i, int j) const
		{
			return (n[i][j]);
		}

		Vector4& operator [](int j)
		{
			return (*reinterpret_cast<Vector4*>(n[j]));
		}

		const Vector4& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector4*>(n[j]));
		}

		//Matrix4 operator *(const Matrix4& a, const Matrix4& b)
		//{
		//	return (Matrix4(a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) + a(0, 3) * b(3, 1),

		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		//					a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0)));
		//}
	};
}