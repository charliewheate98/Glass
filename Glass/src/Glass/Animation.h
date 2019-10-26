#pragma once

#include <vector>
#include <unordered_map>

#include "Timestep.h"
#include "pch.h"
#include "Core.h"
#include "EntityMesh.h"

namespace Glass
{
	struct Frame
	{
		int m_ID;

		Frame() = default;
		Frame(int id) : m_ID(id) {}
		~Frame() { m_ID = 0; }

		operator int() const
		{
			return m_ID;
		}

		Frame& operator ++() {
			m_ID++;
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
		* Reverse Play this Animation
		*/
		void ReversePlay(Timestep ts);

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
		float m_CurrentTimeToNextFrame;
		float m_StartTimeToNextFrame;

		// is the animation playing?
		bool m_IsPlaying;

		// is the animation at looping one?
		bool m_IsLooped;

		// Name of the animation
		std::string m_Name;
	};
	
	/*
		The Animation library stores all the animations loaded in
	*/
	class GLASS_API AnimationLibrary 
	{
	public:
		/*
			Initialise the animation library
		*/
		static void InitialiseLibrary(GLsizei library_size = 0)
		{
			m_Animations.reserve(library_size);
		}

		/*
			Add a animation into the library
		*/
		static void Add(std::shared_ptr<Animation> animation)
		{
			m_Animations.insert({ animation->GetAnimationName(), animation });
		}

		/*
			Check if a animation exists in the library
		*/
		static bool Exists(const std::string name)
		{
			return m_Animations.find(name) != m_Animations.end();
		}

		/*
			Get a animation from the list by name
		*/
		static std::shared_ptr<Animation>& GetAnimationByName(const std::string& name)
		{
			if (Exists(name))
				return m_Animations[name];
			else
				LOG_ERROR("Animation Does Not Exist!");
		
			return m_Animations[NULL];
		}
	private:
		// List of all the animations
		static std::unordered_map<std::string, std::shared_ptr<Animation>> m_Animations;
	};
};



