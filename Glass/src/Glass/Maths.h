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

		Vector3D(float xc, float yc, float zc) :
			x(xc),
			y(yc),
			z(zc)
		{}
		
		~Vector3D()
		{}

		Vector3D operator *=(float s)
		{
			x *= s;
			y *= s;
			z *= s;
			return (*this);
		}

		Vector3D operator /=(float s)
		{
			s = 1.0f / s;
			x /= s;
			y /= s;
			z /= s;
			return (*this);
		}

		inline float Magnitude(const Vector3D& v)
		{
			return (std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
		}
	
		inline Vector3D Normalise(const Vector3D& v)
		{
			return (Vector3D(v.x / Magnitude(v), v.y / Magnitude(v), v.z / Magnitude(v)));
		}
	};

	inline Vector3D operator +(const Vector3D& a, const Vector3D& b)
	{
		return (Vector3D(a.x + b.x, a.y + b.y, a.z + b.z));
	}

	inline Vector3D operator -(const Vector3D& a, const Vector3D& b)
	{
		return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	struct Matrix4
	{
	};
}