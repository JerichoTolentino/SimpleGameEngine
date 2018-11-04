#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace SimpleGameEngine
{
	class SGE_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger> & getCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger> & getClientLogger() { return s_clientLogger; }



	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

// Core log macros
#define SGE_CORE_FATAL(...)		::SimpleGameEngine::Log::getCoreLogger()->fatal(__VA_ARGS__)
#define SGE_CORE_ERROR(...)		::SimpleGameEngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define SGE_CORE_WARNING(...)	::SimpleGameEngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SGE_CORE_INFO(...)		::SimpleGameEngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define SGE_CORE_TRACE(...)		::SimpleGameEngine::Log::getCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define SGE_FATAL(...)		::SimpleGameEngine::Log::getClientLogger()->fatal(__VA_ARGS__)
#define SGE_ERROR(...)		::SimpleGameEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define SGE_WARNING(...)	::SimpleGameEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define SGE_INFO(...)		::SimpleGameEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define SGE_TRACE(...)		::SimpleGameEngine::Log::getClientLogger()->trace(__VA_ARGS__)