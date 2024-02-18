#pragma once

#include "Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include "spdlog/spdlog.h"

#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace Sophon {
    class Log {
    public:
        static void Init();

        static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// GLM to_string() Helpers
template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
    return os << glm::to_string(vector);
}

template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
    return os << glm::to_string(matrix);
}

template <typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
    return os << glm::to_string(quaternion);
}

// Core log macros
#define SFN_CORE_TRACE(...) ::Sophon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SFN_CORE_INFO(...) ::Sophon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SFN_CORE_WARN(...) ::Sophon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SFN_CORE_ERROR(...) ::Sophon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SFN_CORE_CRITICAL(...) ::Sophon::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SFN_CLIENT_TRACE(...) ::Sophon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SFN_CLIENT_INFO(...) ::Sophon::Log::GetClientLogger()->info(__VA_ARGS__)
#define SFN_CLIENT_WARN(...) ::Sophon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SFN_CLIENT_ERROR(...) ::Sophon::Log::GetClientLogger()->error(__VA_ARGS__)
#define SFN_CLIENT_CRITICAL(...) ::Sophon::Log : GetClientLogger()->critical(__VA_ARGS__)
