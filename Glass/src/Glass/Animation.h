#pragma once

#include <vector>
#include "Timestep.h"
#include "pch.h"
#include "Core.h"
#include "EntityMesh.h"

namespace Glass
{
	struct Frame
	{
		int m_Index;

		Frame() = default;
		Frame(int index) : m_Index(index) {}
		~Frame() { m_Index = 0; }

		operator int() const
		{
			return m_Index;
		}

		Frame& operator ++() {
			m_Index++;
		}
	};

	class GLASS_API Animation : public Object
	{
	public:
		Animation(std::shared_ptr<EntityMesh> mesh, glm::vec3 position, std::vector<Frame> frames,
			uint32_t num_frames, float time_to_next_frame = 3.f);
		~Animation();

		/*
		* Get the mesh that this animation is using
		*/
		EntityMesh& GetCoreMesh() { return (*m_Mesh); }

		/*
		* Is the Animation set to looping
		*/
		bool& isLooped()			 { return m_IsLooped; }

		/*
		* Is this animation playing
		*/
		bool& isPlaying()			 { return m_IsPlaying; }

		/*
		* Get the animation name (of type const)
		*/
		std::string GetAnimationName() { return m_Name; }

		/*
		* Get the number of frames this animation is using
		*/
		uint32_t& GetNumberOfFrame() { return m_NumFrames; }

		/*
		* Get Current Frame 
		*/
		uint32_t& GetCurrentFrame()  { return m_CurrentFrame; }

		/*
		* Increment the current frame depending on conditions
		*/
		void IncrementFrame(Timestep ts);

		/*
		* Decrement the current frame depending on conditions
		*/
		void DecrementFrame(Timestep ts);
		
		/*
		* Play this animation
		*/
		void Play(Timestep ts);

		/*
		* Pause the animation 
		*/
		void Pause();

		/*
		* Stop the animation immediately
		*/
		void Stop();

		/*
		* Set the name of the animation
		*/
		void SetAnimationName(std::string name) { m_Name = name; }
	private:
		// list of all the frame
		std::vector<Frame> m_Frames;

		// The Mesh that is being used for the animation
		std::shared_ptr<EntityMesh> m_Mesh;

		// Number of frames
		uint32_t m_NumFrames;

		// Stores the current frame the animation is at
		uint32_t m_CurrentFrame;

		// delay time till the next frame 
		float m_TimeToNextFrame;

		// is the animation playing?
		bool m_IsPlaying;

		// is the animation at looping one?
		bool m_IsLooped;

		// Name of the animation
		std::string m_Name;
	};
	
	class GLASS_API AnimationLibrary {};
};



