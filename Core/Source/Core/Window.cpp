#include "sfnpch.h"

#include "Window.h"

#ifdef SFN_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Sophon {
Scope<Window> Window::Create(const WindowProps& props)
{
#ifdef SFN_PLATFORM_WINDOWS
    return CreateScope<WindowsWindow>(props);
#else
    SFN_CORE_ASSERT(false, "Unknown platform!");
    return nullptr;
#endif
}
}