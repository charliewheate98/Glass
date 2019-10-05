#pragma once

#include "pch.h"
#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#pragma warning(disable:4251)

namespace Glass
{
	class GLASS_API Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> MainLogger;
	public:
		static void Create();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return MainLogger; }
	};
}

#define LOG_TRACE(...)  ::Glass::Logger::GetLogger()->trace(__VA_ARGS__);
#define LOG_INFO(...)   ::Glass::Logger::GetLogger()->info (__VA_ARGS__);
#define LOG_WARN(...)   ::Glass::Logger::GetLogger()->warn (__VA_ARGS__);
#define LOG_ERROR(...)  ::Glass::Logger::GetLogger()->error(__VA_ARGS__);



