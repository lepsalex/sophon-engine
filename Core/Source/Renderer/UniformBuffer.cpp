#include "sfnpch.h"
#include "UniformBuffer.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Platform/Metal/MetalUniformBuffer.hpp"

namespace Sophon {

    Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLUniformBuffer>(size, binding);
        case RendererAPI::API::Metal:
            return CreateRef<MetalUniformBuffer>(size, binding);
        }

        SFN_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
