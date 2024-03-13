#pragma once

#include "Renderer/Buffer.h"

namespace Sophon {
    class MetalVertexBuffer : public VertexBuffer {
    public:
        MetalVertexBuffer(uint32_t size);
        MetalVertexBuffer(float* vertices, uint32_t size);
        virtual ~MetalVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetData(const void* data, uint32_t size) override;

        virtual const BufferLayout& GetLayout() const override { return m_Layout; }
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class MetalIndexBuffer : public IndexBuffer {
    public:
        MetalIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~MetalIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}
