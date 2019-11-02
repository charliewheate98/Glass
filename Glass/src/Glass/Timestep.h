#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API	VariableTimestep
	{
	public:
		VariableTimestep() = default;
		VariableTimestep(float time) : m_Time(time) {}
		~VariableTimestep() {}

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