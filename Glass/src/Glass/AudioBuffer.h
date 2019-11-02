#pragma once

#include "pch.h"
#include "Core.h"
#include "Logger.h"
#include <al.h>
#include <alc.h>

namespace Glass
{
	/*
		Handles the data for a single audio source
	*/
	// channel, sampleRate, bps, size (contained within a struct)
	class AudioSource {};

	/*
		Sets up the OpenAL context and device
	*/
	class AudioContext 
	{
	public:
		AudioContext()
		{
			// Open the audio device. 
			// DEVICE MANAGEMENT
			m_Device = alcOpenDevice(NULL);

			// check if it was not succesfully initialised
			if (m_Device == NULL)
			{
				// if so. Log it and exit out of the constructer
				LOG_ERROR("cannot open sound card");
				return;
			}

			// Create the openal context
			// CONTEXT MANAGEMENT
			m_Context = alcCreateContext(m_Device, NULL);

			// check if it was not succesfully initialised
			if (m_Context == NULL)
			{
				// if so. Log it and exit out of the constructer
				LOG_ERROR("cannot open context");
				return;
			}

			// Actually Make the OpenAL context
			alcMakeContextCurrent(m_Context);
		}

		// Destructer. 
		~AudioContext() 
		{
			// free the device and context from memory
			delete m_Device;
			delete m_Context;

			// Destroy the context completely
			alcDestroyContext(m_Context);
		}

		// Getters.
		inline ALCdevice  & GetDevice()  { return *m_Device;  } // get the device manager
		inline ALCcontext & GetContext() { return *m_Context; } // get the current context 
	private:
		ALCdevice*  m_Device; // device manager
		ALCcontext* m_Context; // [al] context
	};

	/*
		Stores the audio data which can then be played through the audio source
	*/
	class AudioBuffer 
	{
	public:
		// Constructer.
		AudioBuffer(char* data);
		
		// Destructer.
		~AudioBuffer();

		// Getters.
		ALuint  &GetCoreBuffer() { return audio_data.m_Buffer; } // Get the core buffer ID
		ALuint  &GetFormat()	 { return audio_data.m_Format; } // get the format
		ALsizei &GetSize()		 { return audio_data.m_Size;   } // get the audio data size
	private:
		/*
			this struct contains all the audio data stored within the buffer (apart from the buffer id itself)
		*/
		typedef struct
		{
			ALuint  m_Buffer;
			ALuint  m_Format;	
			ALsizei m_Size;
			ALsizei m_Freq;
		} _audio_data;	
		_audio_data audio_data;
	};

	/*
		A library for all the audio sources
	*/
	class AudioLibrary {};
}



