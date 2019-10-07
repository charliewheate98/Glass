#pragma once

#include "pch.h"
#include <iostream>

namespace Glass
{
	struct Vector3D
	{
		float x;
		float y;
		float z;
		float w;

		Vector3D(float xc, float yc, float zc, float wc = 0.f) :
			x(xc),
			y(yc),
			z(zc),
			w(wc)
		{}
		
		~Vector3D()
		{}

		Vector3D operator *=(float s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return (*this);
		}

		Vector3D operator /=(float s)
		{
			s = 1.0f / s;
			x /= s;
			y /= s;
			z /= s;
			w /= s;
			return (*this);
		}

		inline float Magnitude(const Vector3D& v)
		{
			return (std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
		}
	
		inline Vector3D Normalise(const Vector3D& v)
		{
			return (Vector3D(v.x / Magnitude(v), v.y / Magnitude(v), v.z / Magnitude(v), v.w / Magnitude(v)));
		}
	};

	inline Vector3D operator +(const Vector3D& a, const Vector3D& b)
	{
		return (Vector3D(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
	}

	inline Vector3D operator -(const Vector3D& a, const Vector3D& b)
	{
		return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
	}

	struct Matrix4
	{
	private:
		float n[4][4];

		Matrix4() = default;

		Matrix4(Vector3D& a, Vector3D& b, Vector3D& c, Vector3D& d)
		{
			n[0][0] = a.x;  n[0][1] = a.y;  n[0][2] = a.z;  n[0][3] = a.w;
			n[1][0] = b.x;  n[1][1] = b.y;  n[1][2] = b.z;  n[1][3] = b.w;
			n[2][0] = c.x;  n[2][1] = c.y;  n[2][2] = c.z;  n[2][3] = c.w;
			n[3][0] = d.x;  n[3][1] = d.y;  n[3][2] = d.z;  n[3][3] = d.w;
		}

		float& operator ()(int i, int j)
		{
			return (n[i][j]);
		}

		const float& operator ()(int i, int j) const
		{
			return (n[i][j]);
		}

		Vector3D& operator [](int j) 
		{
			return (*reinterpret_cast<Vector3D*>(n[j]));
		}

		const Vector3D& operator [](int j) const
		{
			return (*reinterpret_cast<const Vector3D*>(n[j]));
		}
	};
}