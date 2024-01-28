#pragma once

#include <memory>

#ifdef SFN_DEBUG
#if defined(SFN_PLATFORM_WINDOWS)
#define SFN_DEBUGBREAK() __debugbreak()
#elif defined(SFN_PLATFORM_LINUX)
#include <signal.h>
#define SFN_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define SFN_ENABLE_ASSERTS
#else
#define SFN_DEBUGBREAK()
#endif

// TODO: Bitshifting ... nuff said
#define BIT(x) (1 << x)

// TODO: Need to understand these better, looks like recursive macros, pretty cool!
#define SFN_EXPAND_MACRO(x) x
#define SFN_STRINGIFY_MACRO(x) #x

// TODO: This macro from TheCherno is wild, need to understand it more
#define SFN_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Sophon {

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
// Make a scoped pointer via std::make_unique
constexpr Scope<T> CreateScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
// Make a shared ref-counted pointer via std::make_shared
constexpr Ref<T> CreateRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

}

#include "Core/Log.h"

#include "Core/Assert.h"