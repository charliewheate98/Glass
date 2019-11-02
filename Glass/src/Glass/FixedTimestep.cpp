#include "pch.h"
#include "FixedTimestep.h"

namespace Glass
{
	Timestep::Timestep(double fps)
	{
		elapsed = 0;
		frames_per_second = fps;
		ms = MICRO_SECOND / fps;	// Syncs updates at 60 per second (59 - 61)

		Start();
	}

	double& Timestep::GetFramesPerSecond()
	{
		return frames_per_second;
	}

	void Timestep::SetFramesPerSecond(double value)
	{
		frames_per_second = value;
	}

	void Timestep::SetRate(double value)
	{
		r = value;
	}

	// Start recording current time (called outside of while loop)
	void Timestep::Start()
	{
		QueryPerformanceCounter(&end);
	}

	void Timestep::CalcLastElapsed()
	{
		QueryPerformanceCounter(&start);
		elapsed += (double)(start.QuadPart - end.QuadPart) / ms;
	}

	void Timestep::ResetElapsed()
	{
		elapsed -= 1.0;
	}

	void Timestep::Lock()
	{
		end = start;
	}

	bool Timestep::timeElapsed()
	{
		return (elapsed >= 1.0);
	}
}

