#include "sfnpch.h"
#include "Window.h"

#include "Platform/Universal/GLFWWindow.h"

namespace Sophon {
    Scope<Window> Window::Create(const WindowProps& props)
    {
        return CreateScope<GLFWWindow>(props);
        SFN_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;

    }
}
