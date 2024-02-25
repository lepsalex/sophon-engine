#include "sfnpch.h"

#include "Platform/OpenGL/OpenGlContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sophon {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        SFN_CORE_ASSERT(windowHandle, "OpenGLContext::OpenGLContext: windowHandle is null!")
    }
    void OpenGLContext::Init()
    {
        SFN_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SFN_CORE_ASSERT(status, "OpenGLContext::Init: Failed to initialize Glad!");

        SFN_CORE_INFO("OpenGL Info:");
        SFN_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        SFN_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        SFN_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

        SFN_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "OpenGLContext::Init: Sophon Engine requires at least OpenGL version 4.5!");
    }
    void OpenGLContext::SwapBuffers()
    {
        SFN_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }
}
