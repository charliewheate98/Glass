#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API Timestep
	{
	public:
		Timestep() = default;
		Timestep(float time) : m_Time(time) {}
		~Timestep() {}

		operator float() const
		{
			return m_Time;
		}

		inline float GetSeconds() { return m_Time; }
		inline float GetMilliseconds() { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}