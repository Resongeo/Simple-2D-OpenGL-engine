#pragma once

#include <memory>
#include <stdlib.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cobalt
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; };

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

#define CB_LOG_INFO(...)	::Cobalt::Log::GetLogger()->info(__VA_ARGS__)
#define CB_LOG_WARN(...)	::Cobalt::Log::GetLogger()->warn(__VA_ARGS__)
#define CB_LOG_ERROR(...)	::Cobalt::Log::GetLogger()->error(__VA_ARGS__)

// Inspired by Hazel's log system by The Cherno https://github.com/TheCherno/Hazel