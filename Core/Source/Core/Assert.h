#pragma once

#ifdef SFN_ENABLE_ASSERTS

#define SFN_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
    {                                                   \
        if (!(check)) {                                 \
            SFN##type##ERROR(msg, __VA_ARGS__);         \
            SFN_DEBUGBREAK();                           \
        }                                               \
    }
#define SFN_INTERNAL_ASSERT_WITH_MSG(type, check, ...) SFN_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define SFN_INTERNAL_ASSERT_NO_MSG(type, check) SFN_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", SFN_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define SFN_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define SFN_INTERNAL_ASSERT_GET_MACRO(...) SFN_EXPAND_MACRO(SFN_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SFN_INTERNAL_ASSERT_WITH_MSG, SFN_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define SFN_ASSERT(...) SFN_EXPAND_MACRO(SFN_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define SFN_CORE_ASSERT(...) SFN_EXPAND_MACRO(SFN_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))

// Common Error Messages
#define SFN_ERR_RENDER_API_NONE_NOT_SUPPORTED "RendererAPI::None is not currently supported!"
#define SFN_ERR_UNKOWN_RENDER_API "Unknown RendererAPI!"

#else
#define SFN_ASSERT(...)
#define SFN_CORE_ASSERT(...)
#endif
