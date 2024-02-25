#include "sfnpch.h"
#include "Renderer/Texture.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Sophon {

    Ref<Texture2D> Texture2D::Create(const TextureSpecification& specification, const TextureOptions& options)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(specification, options);
        }

        SFN_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path, const TextureOptions& options)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(path, options);
        }

        SFN_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
