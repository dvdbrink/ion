#pragma once

#include <ion/gfx/gl/resource.hpp>
#include <ion/gfx/pixel_format.hpp>
#include <ion/gfx/image.hpp>

#include <vector>

namespace ion { namespace gfx { namespace gl
{
    enum class InternalFormat
    {
        R8
    };

    enum class Wrapping
    {
        ClampEdge,
        ClampBorder,
        Repeat,
        MirroredRepeat
    };

    enum class Filter
    {
        Nearest,
        Linear,
        NearestMipmapNearest,
        LinearMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapLinear
    };

    class Texture : public Resource<Texture>
    {
    public:
        Texture(const Texture&);
        Texture(const Image&);
        Texture(InternalFormat internalFormat, unsigned int width, unsigned int height, Format format, Type type);

        Texture& operator=(const Texture&);

        void setPixels(const unsigned char*, int xOffset, int yOffset, unsigned int width, unsigned int height);
        void setPixels(const std::vector<uint8_t>& pixels, int xOffset, int yOffset, unsigned int width, unsigned int height);

        void setWrapping(Wrapping s);
        void setWrapping(Wrapping s, Wrapping t);
        void setWrapping(Wrapping s, Wrapping t, Wrapping r);

        void setFilter(Filter min, Filter mag);

        void generateMipMaps();

        void bind() const;
        void unbind() const;

        unsigned int getWidth() const;
        unsigned int getHeight() const;

    private:
        unsigned int width;
        unsigned int height;
    };
}}}