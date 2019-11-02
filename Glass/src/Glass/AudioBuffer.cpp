#include "AudioBuffer.h"
#include "Logger.h"

namespace Glass
{
	AudioBuffer::AudioBuffer(char* data)
	{
		// Catch Any Errors
		alGetError();

		// If there was an error. Then Log it.
		if (alGetError() != AL_NO_ERROR)
		{
			// Log the error.
			LOG_ERROR("Unable to generate a valid audio buffer!");
		}

		// Generate the buffer
		alGenBuffers(1, &audio_data.m_Buffer);

		// Store the audio data within the buffer
		alBufferData(audio_data.m_Buffer, audio_data.m_Format, data, audio_data.m_Size, audio_data.m_Freq);
	}

	AudioBuffer::~AudioBuffer()
	{
		audio_data.m_Format = NULL;
		audio_data.m_Size   = NULL;
		audio_data.m_Freq   = NULL;

		alDeleteBuffers(1, &audio_data.m_Buffer);
	}
}