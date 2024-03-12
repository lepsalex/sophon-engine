#include "sfnpch.h"
#include "Window.h"

#ifdef SFN_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

#ifdef SFN_PLATFORM_MACOS
#define GLFW_EXPOSE_NATIVE_COCOA
#include "Platform/MacOS/MacOSWindow.h"
#endif

namespace Sophon {
    Scope<Window> Window::Create(const WindowProps& props)
    {
#if defined(SFN_PLATFORM_WINDOWS)
        return CreateScope<WindowsWindow>(props);
#elif defined(SFN_PLATFORM_MACOS)
        return nullptr;
#else
        SFN_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
#endif
    }
}
