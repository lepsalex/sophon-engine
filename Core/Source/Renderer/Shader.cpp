#include "sfnpch.h"
#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sophon {
    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, SFN_ERR_RENDER_API_NONE_NOT_SUPPORTED);
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        SFN_CORE_ASSERT(false, SFN_ERR_UNKOWN_RENDER_API);
        return nullptr;
    }
}
