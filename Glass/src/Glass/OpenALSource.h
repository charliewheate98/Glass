#pragma once

#include <al.h>
#include <alc.h>

#include "pch.h"
#include "Core.h"
#include "Logger.h"

namespace Glass
{
	class WavLoader
	{
	public:
		static bool isBigEndian()
		{
			int a = 1;
			return !((char*)&a)[0];
		}

		static int convertToInt(char* buffer, int len)
		{
			int a = 0;
			if (!isBigEndian())
				for (int i = 0; i < len; i++)
					((char*)&a)[i] = buffer[i];
			else
				for (int i = 0; i < len; i++)
					((char*)&a)[3 - i] = buffer[i];
			return a;
		}

		static char* Load(const char* wav_file, 
			int& chan, int& samplerate, int& bps, int& size)
		{
			char buffer[4];

			std::ifstream inFile(wav_file, std::ios::binary);

			inFile.read(buffer, 4);

			if (strncmp(buffer, "RIFF", 4) != 0)
			{
				LOG_INFO("This is not a valid wav file");
				return NULL;
			}

			inFile.read(buffer, 4);
			inFile.read(buffer, 4);
			inFile.read(buffer, 4);
			inFile.read(buffer, 4);
			inFile.read(buffer, 2);
			inFile.read(buffer, 2);
			chan = convertToInt(buffer, 2);
			inFile.read(buffer, 4);
			samplerate = convertToInt(buffer, 4);
			inFile.read(buffer, 4);
			inFile.read(buffer, 2);
			inFile.read(buffer, 2);
			bps = convertToInt(buffer, 2);
			inFile.read(buffer, 4);
			inFile.read(buffer, 4);
			size = convertToInt(buffer, 4);
			char* data = new char[size];
			inFile.read(data, size);

			return data;
		}
	};

	class GLASS_API OpenALSource
	{
	public:
		OpenALSource();
		~OpenALSource();
	private:
		ALuint m_Buffer;
	};
}



