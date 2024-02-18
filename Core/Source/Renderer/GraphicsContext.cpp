#include "sfnpch.h"

#include "Renderer/GraphicsContext.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Sophon {
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        // TODO: This method could return other types of contexts (Vulkan, DirectX, etc)
        return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }
}
