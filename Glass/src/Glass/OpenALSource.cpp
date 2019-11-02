#include "OpenALSource.h"
#include "Logger.h"

namespace Glass
{
	OpenALSource::OpenALSource()
	{
		int channel, sampleRate, bps, size;

		char* data = WavLoader::Load("Content/Sounds/bgm.wav", channel, sampleRate, bps, size);

		ALCdevice* device = alcOpenDevice(NULL);
		if (device == NULL)
		{
			std::cout << "cannot open sound card" << std::endl;
		}

		ALCcontext* context = alcCreateContext(device, NULL);
		if (context == NULL)
		{
			std::cout << "cannot open context" << std::endl;
		}

		alcMakeContextCurrent(context);

		unsigned int bufferid, format;

		alGenBuffers(1, &bufferid);
		
		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else 
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else 
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else 
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		alBufferData(bufferid, format, data, size, sampleRate);
		
		unsigned int sourceid;

		alGenSources(1, &sourceid);
		alSourcei(sourceid, AL_BUFFER, bufferid);
		alSourcePlay(sourceid);

		LOG_TRACE("Wav File is Currently Playing");
	}

	OpenALSource::~OpenALSource()
	{
		alDeleteBuffers(1, &m_Buffer);
	}
}