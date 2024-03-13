#include "sfnpch.h"

#include "Renderer/Renderer.h"
#include "Renderer/GraphicsContext.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/Metal/MetalContext.hpp"

namespace Sophon {
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        case RendererAPI::API::Metal:
            return CreateScope<MetalContext>(static_cast<GLFWwindow*>(window));;
        }

        SFN_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
