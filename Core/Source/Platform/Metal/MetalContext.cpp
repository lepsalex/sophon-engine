#include "sfnpch.h"

#include "Platform/Metal/MetalContext.hpp"

#include <GLFW/glfw3.h>

namespace Sophon {
    MetalContext::MetalContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        SFN_CORE_ASSERT(windowHandle, "MetalContext::MetalContext: windowHandle is null!")
    }

    void MetalContext::Init()
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalContext::SwapBuffers()
    {
        SFN_PROFILE_FUNCTION();
    }
}
