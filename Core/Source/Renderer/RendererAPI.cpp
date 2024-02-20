#include "sfnpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sophon {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API) {
        case RendererAPI::API::None:
            SFN_CORE_ASSERT(false, SFN_ERR_RENDER_API_NONE_NOT_SUPPORTED);
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLRendererAPI>();
        }

        SFN_CORE_ASSERT(false, SFN_ERR_UNKOWN_RENDER_API);
        return nullptr;
    }
}
