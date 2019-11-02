#pragma once

#include <vector>
#include <unordered_map>

#include "Timestep.h"
#include "pch.h"
#include "Core.h"
#include "EntityMesh.h"

namespace Glass
{
	/*
		This class represents a single Frame
	*/
	class Frame
	{
	private:
		// the frame id/index
		int m_ID;
	public:
		/*
			Default Constructer to prevent initialisation errors
		*/
		Frame() = default;

		/*
			Constructer. initiaise the id/index
		*/
		Frame(int id) : m_ID(id) {}

		/*
			Destructer, set the id/index to be NULL when memory is deallocated/free'd
		*/
		~Frame() { m_ID = NULL; }

		/*
			Handle the user to present a frame object as a index/integer
		*/
		operator int() const
		{
			return m_ID;
		}

		/*
			When I do 'Frame++' this will increment the frame index
		*/
		Frame operator ++(int) {
			m_ID++;
			return *this;
		}
	};

	class GLASS_API Animation : public Object
	{
	public:
		/*
			Constructer. Initialise an animations
		*/
		Animation(std::shared_ptr<EntityMesh> mesh, glm::vec3 position, std::vector<Frame> frames,
			uint32_t num_frames, float time_to_next_frame = 3.f);

		/*
			Free memory when out of scope
		*/
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
		void IncrementFrame();

		/*
		* Decrement the current frame depending on conditions
		*/
		void DecrementFrame();
		
		/*
		* Play this animation
		*/
		void Play();

		/*
		* Reverse Play this Animation
		*/
		void ReversePlay();

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
			LOG_TRACE("Animation '{0}' Pushed into the Animation Library", animation->GetAnimationName());
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



