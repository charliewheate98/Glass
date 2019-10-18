#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API BaseTexture
	{
	public:
		virtual ~BaseTexture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot) const = 0;
	};

	class GLASS_API Texture2D : public BaseTexture
	{
	public:
		static SharedScope<Texture2D> Create(const std::string& file);
	};
}


