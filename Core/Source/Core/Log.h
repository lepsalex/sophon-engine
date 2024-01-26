#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Sophon {
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define SFN_CORE_TRACE(...)			::Sophon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SFN_CORE_INFO(...)			::Sophon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SFN_CORE_WARN(...)			::Sophon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SFN_CORE_ERROR(...)			::Sophon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SFN_CORE_CRITICAL(...)		::Sophon::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SFN_CLIENT_TRACE(...)		::Sophon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SFN_CLIENT_INFO(...)		::Sophon::Log::GetClientLogger()->info(__VA_ARGS__)
#define SFN_CLIENT_WARN(...)		::Sophon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SFN_CLIENT_ERROR(...)		::Sophon::Log::GetClientLogger()->error(__VA_ARGS__)
#define SFN_CLIENT_CRITICAL(...)	::Sophon::Log:GetClientLogger()->critical(__VA_ARGS__)