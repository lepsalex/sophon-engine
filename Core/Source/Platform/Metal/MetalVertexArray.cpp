#include "sfnpch.h"
#include "Platform/Metal/MetalVertexArray.hpp"

namespace Sophon {

    MetalVertexArray::MetalVertexArray()
    {
        SFN_PROFILE_FUNCTION();
    }

    MetalVertexArray::~MetalVertexArray()
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalVertexArray::Bind() const
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalVertexArray::Unbind() const
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        SFN_PROFILE_FUNCTION();

        vertexBuffer->Bind();

        SFN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");
    }

    void MetalVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        SFN_PROFILE_FUNCTION();

        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

}
