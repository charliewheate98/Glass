#include "Animation.h"

namespace Glass
{
	/*
		Static Initialisations
	*/
	std::unordered_map<std::string, std::shared_ptr<Animation>> AnimationLibrary::m_Animations;

	/*
		Constructer. Initialise all the variables and objects here.
	*/
	Animation::Animation(std::shared_ptr<EntityMesh> mesh, glm::vec3 position, std::vector<Frame> frames, uint32_t num_frames, float time_to_next_frame) :
		m_Mesh(mesh), // the mesh being used for the animation
		m_NumFrames(num_frames), // the maximum number of frames
		m_CurrentTimeToNextFrame(time_to_next_frame), // The time is takes to transition to the next frame
		m_Frames(frames), // the list of all the frames
		m_CurrentFrame(0),
		m_IsLooped(true), // Is this Animation Looping?
		m_IsPlaying(true) // Is this Animation Currently Playing?
	{
		// Initialise the position from the base interface (Object)
		m_Position = position;
		m_StartTimeToNextFrame = m_CurrentTimeToNextFrame;

		// size the vector depending on the 
		frames.resize(m_NumFrames);
	}

	/*
		Destructer. Free all the objects here from memory.
	*/
	Animation::~Animation() 
	{
		m_Frames.clear();

		for (Frame frame : m_Frames)
			delete &frame;

		m_CurrentTimeToNextFrame = NULL;
		m_IsPlaying = NULL;
		m_IsLooped = NULL;
	}

	/*
		Increment the frames
	*/
	void Animation::IncrementFrame()
	{
		// Update the texture index
		m_Mesh->SetTextureIndex(m_Frames[m_CurrentFrame]); 
			
		// Decrement the timer by timestep
		m_CurrentTimeToNextFrame -= 0.1f;

		// If there are more then 0 frames
		if (m_Frames.size() > 0 && m_IsPlaying)
		{
			// if the time to next frame is 0
			// then we are ready to go to the next frame
			if (m_CurrentTimeToNextFrame <= 0.f)
			{
				// Increment to the next frame
				//m_CurrentFrame++;
				m_CurrentFrame++;

				// if this animation is not a looping animation then 
				// stop is at the last frame and return.
				// -----
				// else reset the animation
				if (!m_IsLooped)
				{
					if(m_CurrentFrame >= m_NumFrames)
					{
						m_CurrentFrame = m_Frames[0];
						m_IsPlaying = false;
					}
				}
				else 
				{
					// if the current frame has reach the maximum and looping is set to true
					// then reset the animation
					if (m_CurrentFrame >= m_NumFrames)
					{
						m_CurrentFrame = m_Frames[0];
					}
				}

				// Reset the Delay Timer
				m_CurrentTimeToNextFrame = m_StartTimeToNextFrame;
				m_CurrentTimeToNextFrame -= 0.1f;
			}
		}
		else if(m_Frames.size() <= 0)
			LOG_ERROR("[IncrementFrame] Unable to Play Animation. Not Enough Frames");
	}

	/*
		Decrement the frames
	*/
	void Animation::DecrementFrame()
	{
		// Update the texture index
		m_Mesh->SetTextureIndex(m_CurrentFrame);

		// Decrement the timer by timestep
		m_CurrentTimeToNextFrame -= 0.1f;

		// if there are more then 0 frames
		if (m_Frames.size() > 0)
		{
			// if the time to next frame is 0
			// then we are ready to go to the next frame
			if (m_CurrentTimeToNextFrame <= 0.f)
			{
				// we are now playing the animation
				m_IsPlaying = true;

				// Increment to the next frame
				m_CurrentFrame--;

				// if this animation is not a looping animation then 
				// stop is at the last frame and return.
				// -----
				// else reset the animation
				if (!m_IsLooped)
				{
					m_CurrentFrame >= m_NumFrames ? m_CurrentFrame = m_NumFrames : NULL;
				}
				else
				{
					// if the current frame has reach the maximum and looping is set to true
					// then reset the animation
					if (m_CurrentFrame >= m_NumFrames)
					{
						m_CurrentFrame = 0;
					}
				}

				// Reset the Delay Timer1
				m_CurrentTimeToNextFrame = m_StartTimeToNextFrame;
				m_CurrentTimeToNextFrame -= 0.1f;
			}
		}
		else
			LOG_ERROR("[IncrementFrame] Unable to Play Animation. Not Enough Frames");
	}

	/*
		Play the animation
	*/
	void Animation::Play()
	{
		IncrementFrame();
	}

	/*
		Play the Animation in reverse
	*/
	void Animation::ReversePlay()
	{
		DecrementFrame();
	}

	/*
		Pause the animation at its current frame
	*/
	void Animation::Pause()
	{
		if (m_IsPlaying)
			m_CurrentFrame = m_CurrentFrame;
	}

	/*
		Stop the animation and reset
	*/
	void Animation::Stop() 
	{
		if(m_IsPlaying)
			m_CurrentFrame = 0;
	}
}