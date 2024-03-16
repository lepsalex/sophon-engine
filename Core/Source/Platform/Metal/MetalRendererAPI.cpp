#include "sfnpch.h"
#include "Platform/Metal/MetalRendererAPI.hpp"

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

namespace Sophon {

    void MetalRendererAPI::Init()
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
    }

    void MetalRendererAPI::SetClearColor(const glm::vec4& color)
    {
    }

    void MetalRendererAPI::Clear()
    {
    }

    void MetalRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
    {
    }
}
