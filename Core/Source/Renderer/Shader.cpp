#include "sfnpch.h"
#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sophon {
    Ref<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            #ifndef SFN_PLATFORM_MACOS
            return CreateRef<OpenGLShader>(filepath);
            #else
            SFN_CORE_ASSERT(false, "RendererAPI::OpenGL is not supported on MacOS!");
            return nullptr;
            #endif
        case RendererAPI::API::Metal:
            #ifdef SFN_PLATFORM_MACOS
            return nullptr;
            #else
            SFN_CORE_ASSERT(false, "RendererAPI::Metal is only supported on MacOS!");
            return nullptr;
            #endif
        }

        SFN_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            #ifndef SFN_PLATFORM_MACOS
            return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
            #else
            SFN_CORE_ASSERT(false, "RendererAPI::OpenGL is not supported on MacOS!");
            return nullptr;
            #endif
        case RendererAPI::API::Metal:
            #ifdef SFN_PLATFORM_MACOS
            return nullptr;
            #else
            SFN_CORE_ASSERT(false, "RendererAPI::Metal is only supported on MacOS!");
            return nullptr;
            #endif
        }

        SFN_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        SFN_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        SFN_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}
