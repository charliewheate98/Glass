#pragma once

#include "pch.h"
#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

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





