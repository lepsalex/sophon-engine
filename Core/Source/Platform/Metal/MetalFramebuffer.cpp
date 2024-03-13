#include "sfnpch.h"
#include "Platform/Metal/MetalFramebuffer.hpp"

namespace Sophon {
    static const uint32_t s_MaxFramebufferSize = 8192;

    MetalFramebuffer::MetalFramebuffer(const FramebufferSpecification& spec)
        : m_Specification(spec)
    {
        Invalidate();
    }

    MetalFramebuffer::~MetalFramebuffer()
    {
    }

    void MetalFramebuffer::Invalidate()
    {
    }

    void MetalFramebuffer::Bind()
    {
    }

    void MetalFramebuffer::Unbind()
    {
    }

    void MetalFramebuffer::Resize(uint32_t width, uint32_t height)
    {
        if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize) {
            SFN_CORE_WARN("Attempted to resize framebuffer to {0}, {1}", width, height);
            return;
        }
        m_Specification.Width = width;
        m_Specification.Height = height;

        Invalidate();
    }

    int MetalFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
    {
        SFN_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size());
        return 0;
    }

    void MetalFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
    {
        SFN_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size());
    }

}
