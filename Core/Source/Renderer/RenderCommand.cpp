#include "sfnpch.h"
#include "Renderer/RenderCommand.h"

namespace Sophon {
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
