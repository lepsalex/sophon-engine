#include "sfnpch.h"

#include "Renderer/Renderer.h"
#include "Renderer/GraphicsContext.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Sophon {
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, SFN_ERR_RENDER_API_NONE_NOT_SUPPORTED);
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        SFN_CORE_ASSERT(false, SFN_ERR_UNKOWN_RENDER_API);
        return nullptr;
    }
}
