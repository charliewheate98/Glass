#pragma once

#include <unordered_map>
#include "pch.h"
#include "Core.h"
#include "Logger.h"

#include <glm.hpp>

namespace Glass
{
	class GLASS_API BaseTexture
	{
	protected:
		std::string m_Name;
	public:
		virtual ~BaseTexture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		void SetName(std::string name) { m_Name = name; }

		virtual void Bind(uint32_t slot) const = 0;
	};

	class GLASS_API Texture2D : public BaseTexture
	{
	public:
		static SharedScope<Texture2D> Create(const std::string& file, int num_rows);
	private:
		static GLuint loc_NumRows;
	};

	class GLASS_API TextureLibrary
	{
	public:
		static void InitialiseLibrary(size_t library_size = 0)
		{
			m_Textures.reserve(library_size);
		}

		static void Add(const std::string& name, SharedScope<Texture2D> texture)
		{
			texture->SetName(name);
			m_Textures.insert({ name, texture });
		}

		static std::unordered_map<std::string, SharedScope<Texture2D>>& GetTextureList() { return m_Textures; }

		static bool Exists(const std::string& name)
		{
			return m_Textures.find(name) != m_Textures.end();
		}

		static SharedScope<Texture2D>& GetByName(const std::string& name)
		{
			if (Exists(name))
				return m_Textures[name];

			return m_Textures[NULL];
		}
	private:
		static std::unordered_map<std::string, SharedScope<Texture2D>> m_Textures;
	};
}


