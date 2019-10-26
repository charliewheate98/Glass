#include "Animation.h"

namespace Glass
{
	Animation::Animation(std::shared_ptr<EntityMesh> mesh, glm::vec3 position, std::vector<Frame> frames, uint32_t num_frames, float time_to_next_frame) :
		m_Mesh(mesh),
		m_NumFrames(num_frames),
		m_TimeToNextFrame(time_to_next_frame),
		m_Frames(frames),
		m_CurrentFrame(0)
	{
		// Initialise the position from the base interface (Object)
		m_Position = position;

		// size the vector depending on the 
		frames.resize(m_NumFrames);
	}

	Animation::~Animation() {}

	void Animation::IncrementFrame(Timestep ts)
	{
		m_Mesh->SetTextureIndex(m_CurrentFrame);
			
		m_TimeToNextFrame -= ts;

		if (m_Frames.size() > 0)
		{
			if (m_TimeToNextFrame <= 0.f)
			{
				m_IsPlaying = true;

				m_CurrentFrame++;

				if (!m_IsLooped)
				{
					m_CurrentFrame = m_CurrentFrame;
				}

				m_TimeToNextFrame = .5f;
				m_TimeToNextFrame -= ts;
			}
		}
		else
			LOG_ERROR("[IncrementFrame] Unable to Play Animation. Not Enough Frames");
	}

	void Animation::DecrementFrame(Timestep ts)
	{
		m_TimeToNextFrame -= ts;

		if (m_Frames.size() > 0)
		{
			if (m_TimeToNextFrame <= 0.f)
			{
				m_IsPlaying = true;

				m_CurrentFrame--;
				m_TimeToNextFrame = 3.f;

				DecrementFrame(ts);
			}
		}
		else
			LOG_ERROR("[DecrementFrame] Unable to Play Animation. Not Enough Frames");
	}

	void Animation::Play(Timestep ts)
	{
		IncrementFrame(ts);
	}

	void Animation::Pause()
	{
		if (m_IsPlaying)
			m_CurrentFrame = m_CurrentFrame;
	}

	void Animation::Stop()
	{
		if(m_IsPlaying)
			m_CurrentFrame = 0;
	}
}