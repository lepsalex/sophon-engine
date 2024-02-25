#include "sfnpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include <stb_image.h>

namespace Sophon {
    namespace Utils {

        static GLenum ImageFormatToGLDataFormat(ImageFormat format)
        {
            switch (format) {
            case ImageFormat::RGB8:
                return GL_RGB;
            case ImageFormat::RGBA8:
                return GL_RGBA;
            }

            SFN_CORE_ASSERT(false, "Unknown ImageFormat type!");
            return 0;
        }

        static GLenum ImageFormatToGLInternalFormat(ImageFormat format)
        {
            switch (format) {
            case ImageFormat::RGB8:
                return GL_RGB8;
            case ImageFormat::RGBA8:
                return GL_RGBA8;
            }

            SFN_CORE_ASSERT(false, "Unknown ImageFormat type!");
            return 0;
        }

        static GLenum MinMagFilterToGLInternalFormat(MinMagFilter filter)
        {
            switch (filter) {
            case MinMagFilter::LINEAR:
                return GL_LINEAR;
            case MinMagFilter::NEAREST:
                return GL_NEAREST;
            }

            SFN_CORE_ASSERT(false, "Unknown MinMagFilter type!");
            return 0;
        }

        static GLenum WrapOptionToGLInternalFormat(WrapOption option)
        {
            switch (option) {
            case WrapOption::REPEAT:
                return GL_REPEAT;
            case WrapOption::MIRRORED_REPEAT:
                return GL_MIRRORED_REPEAT;
            }

            SFN_CORE_ASSERT(false, "Unknown WrapOption type!");
            return 0;
        }
    }

    OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& specification, const TextureOptions& options)
        : m_Specification(specification)
    {
        m_Width = specification.Width;
        m_Height = specification.Height;

        m_InternalFormat = Utils::ImageFormatToGLInternalFormat(m_Specification.Format);
        m_DataFormat = Utils::ImageFormatToGLDataFormat(m_Specification.Format);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        auto minFilter = Utils::MinMagFilterToGLInternalFormat(options.MinFilter);
        auto magFilter = Utils::MinMagFilterToGLInternalFormat(options.MagFilter);
        auto wrapS = Utils::WrapOptionToGLInternalFormat(options.WrapS);
        auto wrapT = Utils::WrapOptionToGLInternalFormat(options.WrapT);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, minFilter);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, magFilter);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, wrapS);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, wrapT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path, const TextureOptions& options)
        : m_Path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = nullptr;
        {
            SFN_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string& path, const TextureOptions& options)");
            data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        if (data) {
            m_IsLoaded = true;

            m_Width = width;
            m_Height = height;

            GLenum internalFormat = 0, dataFormat = 0;
            if (channels == 4) {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            } else if (channels == 3) {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }

            m_InternalFormat = internalFormat;
            m_DataFormat = dataFormat;

            SFN_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

            glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
            glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

            auto minFilter = Utils::MinMagFilterToGLInternalFormat(options.MinFilter);
            auto magFilter = Utils::MinMagFilterToGLInternalFormat(options.MagFilter);
            auto wrapS = Utils::WrapOptionToGLInternalFormat(options.WrapS);
            auto wrapT = Utils::WrapOptionToGLInternalFormat(options.WrapT);

            glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, minFilter);
            glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, magFilter);
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, wrapS);
            glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, wrapT);

            glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size)
    {
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        SFN_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }
}
