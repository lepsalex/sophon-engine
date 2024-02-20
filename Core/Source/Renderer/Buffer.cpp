#include "sfnpch.h"
#include "Renderer/Buffer.h"

#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Sophon {
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, SFN_ERR_RENDER_API_NONE_NOT_SUPPORTED);
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(size);
        }

        SFN_CORE_ASSERT(false, SFN_ERR_UNKOWN_RENDER_API);
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, SFN_ERR_RENDER_API_NONE_NOT_SUPPORTED);
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        SFN_CORE_ASSERT(false, SFN_ERR_UNKOWN_RENDER_API);
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, SFN_ERR_RENDER_API_NONE_NOT_SUPPORTED);
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(indices, size);
        }

        SFN_CORE_ASSERT(false, SFN_ERR_UNKOWN_RENDER_API);
        return nullptr;
    }
}
