#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Glass
{
	std::shared_ptr<spdlog::logger> Logger::MainLogger;

	void Logger::Create()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		MainLogger = spdlog::stdout_color_mt("APP");
		MainLogger->set_level(spdlog::level::trace);
	}
}

