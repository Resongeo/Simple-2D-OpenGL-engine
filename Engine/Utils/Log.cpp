#include "Log.h"

namespace Cobalt
{
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Logger = spdlog::stderr_color_mt("Engine");
		s_Logger->set_level(spdlog::level::trace);
	}

}