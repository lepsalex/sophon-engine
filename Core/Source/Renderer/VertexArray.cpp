#include "sfnpch.h"
#include "VertexArray.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sophon {
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        }

        SFN_CORE_ASSERT(false, SFN_ERR_UNKOWN_RENDER_API);
        return nullptr;
    }
}
