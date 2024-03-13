#include "sfnpch.h"
#include "Framebuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Platform/Metal/MetalFramebuffer.hpp"

namespace Sophon {
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLFramebuffer>(spec);
        case RendererAPI::API::Metal:
            return CreateRef<MetalFramebuffer>(spec);
        }

        SFN_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
