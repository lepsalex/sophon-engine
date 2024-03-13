#include "sfnpch.h"
#include "Platform/Metal/MetalTexture.hpp"

#include <stb_image.h>

namespace Sophon {
    MetalTexture2D::MetalTexture2D(const TextureSpecification& specification, const TextureOptions& options)
        : m_Specification(specification)
    {
        SFN_PROFILE_FUNCTION();
    }

    MetalTexture2D::MetalTexture2D(const std::string& path, const TextureOptions& options)
        : m_Path(path)
    {
        SFN_PROFILE_FUNCTION();
    }

    MetalTexture2D::~MetalTexture2D()
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalTexture2D::SetData(void* data, uint32_t size)
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalTexture2D::Bind(uint32_t slot) const
    {
        SFN_PROFILE_FUNCTION();
    }
}
