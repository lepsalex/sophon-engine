#include "sfnpch.h"
#include "Platform/Metal/MetalBuffer.hpp"

namespace Sophon {
    /////////////////////////////////////////////////////////////////////////////
    // VertexBuffer /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    MetalVertexBuffer::MetalVertexBuffer(uint32_t size)
    {
        SFN_PROFILE_FUNCTION();
    }

    MetalVertexBuffer::MetalVertexBuffer(float* vertices, uint32_t size)
    {
        SFN_PROFILE_FUNCTION();
    }

    MetalVertexBuffer::~MetalVertexBuffer()
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalVertexBuffer::Bind() const
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalVertexBuffer::Unbind() const
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalVertexBuffer::SetData(const void* data, uint32_t size)
    {
        SFN_PROFILE_FUNCTION();
    }

    /////////////////////////////////////////////////////////////////////////////
    // IndexBuffer //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

    MetalIndexBuffer::MetalIndexBuffer(uint32_t* indices, uint32_t count)
        : m_Count(count)
    {
        SFN_PROFILE_FUNCTION();
    }

    MetalIndexBuffer::~MetalIndexBuffer()
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalIndexBuffer::Bind() const
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalIndexBuffer::Unbind() const
    {
        SFN_PROFILE_FUNCTION();
    }

}
