#include "sfnpch.h"
#include "RendererAPI.h"

#include "Platform/Metal/MetalRendererAPI.hpp"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sophon {

#ifdef SFN_PLATFORM_MACOS
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::Metal;
#else
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
#endif

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
#ifndef SFN_PLATFORM_MACOS
            return CreateScope<OpenGLRendererAPI>();
#else
            SFN_CORE_ASSERT(false, "RendererAPI::OpenGL is not supported on MacOS!");
            return nullptr;
#endif
        case RendererAPI::API::Metal:
#ifdef SFN_PLATFORM_MACOS
            return CreateScope<MetalRendererAPI>();
#else
            SFN_CORE_ASSERT(false, "RendererAPI::Metal is only supported on MacOS!");
            return nullptr;
#endif
        }

        SFN_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
