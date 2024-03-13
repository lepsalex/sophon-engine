#pragma once

#include "Renderer/UniformBuffer.h"

namespace Sophon {

    class MetalUniformBuffer : public UniformBuffer {
    public:
        MetalUniformBuffer(uint32_t size, uint32_t binding);
        virtual ~MetalUniformBuffer();

        virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;

    private:
        uint32_t m_RendererID = 0;
    };
}
