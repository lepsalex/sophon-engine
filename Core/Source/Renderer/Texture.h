#pragma once

namespace Sophon {
    enum class ImageFormat {
        None = 0,
        R8,
        RGB8,
        RGBA8,
        RGBA32F
    };

    // Only supporting linear/nearest for minifying for now
    enum class MinMagFilter {
        LINEAR = 0,
        NEAREST,
    };

    // Only supporting repeat/mirrored-repeat for now
    enum class WrapOption {
        REPEAT = 0,
        MIRRORED_REPEAT,
    };

    struct TextureSpecification {
        uint32_t Width = 1;
        uint32_t Height = 1;
        ImageFormat Format = ImageFormat::RGBA8;
    };

    struct TextureOptions {
        MinMagFilter MinFilter = MinMagFilter::LINEAR;
        MinMagFilter MagFilter = MinMagFilter::LINEAR;
        WrapOption WrapS = WrapOption::REPEAT;
        WrapOption WrapT = WrapOption::REPEAT;
    };

    class Texture {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetRendererID() const = 0;

        virtual const std::string& GetPath() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual bool IsLoaded() const = 0;

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(const TextureSpecification& specification, const TextureOptions& options);
        static Ref<Texture2D> Create(const TextureSpecification& specification)
        {
            return Create(specification, TextureOptions());
        }
        static Ref<Texture2D> Create()
        {
            return Create(TextureSpecification());
        };

        static Ref<Texture2D> Create(const std::string& path, const TextureOptions& options);
        static Ref<Texture2D> Create(const std::string& path)
        {
            return Create(path, TextureOptions());
        };
    };
}
