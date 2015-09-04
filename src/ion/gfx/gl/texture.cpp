#include <ion/gfx/gl/texture.hpp>

#include "error.hpp"
#include "extensions.h"
#include "map.hpp"

namespace ion { namespace gfx { namespace gl
{
    Texture::Texture(InternalFormat internalFormat, unsigned int width, unsigned int height, Format format, Type type) :
        Resource(glGenTextures, glDeleteTextures), width(width), height(height)
    {
        bind();

        check_error(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(internalFormat), width, height, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), 0));

        unbind();
    }

    Texture::Texture(const Image& image) :
        Resource(glGenTextures, glDeleteTextures), width(image.width()), height(image.height())
    {
        bind();

        check_error(glTexImage2D(GL_TEXTURE_2D, 0, gl::map(image.format()), image.width(), image.height(), 0, gl::map(image.format()), gl::map(image.type()), &image.pixels().front()));

        unbind();
    }

    Texture::Texture(const Texture& copy) : Resource(copy) {}

    Texture& Texture::operator=(const Texture& copy)
    {
        Resource::operator=(copy);
        return *this;
    }

    void Texture::setPixels(const unsigned char* ptr, int xOffset, int yOffset, unsigned int width, unsigned int height)
    {
        bind();

        check_error(glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, GL_RED, GL_UNSIGNED_BYTE, ptr));

        unbind();
    }

    void Texture::setPixels(const std::vector<uint8_t>& pixels, int xOffset, int yOffset, unsigned int width, unsigned int height)
    {
        setPixels(&pixels.front(), xOffset, yOffset, width, height);
    }

    void Texture::setWrapping(Wrapping s)
    {
        bind();

        check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(s)));

        unbind();
    }

    void Texture::setWrapping(Wrapping s, Wrapping t)
    {
        bind();

        check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(s)));
        check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(t)));

        unbind();
    }

    void Texture::setWrapping(Wrapping s, Wrapping t, Wrapping r)
    {
        bind();

        check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(s)));
        check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(t)));
        check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(r)));

        unbind();
    }

    void Texture::setFilter(Filter min, Filter mag)
    {
        bind();

        check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(min)));
        check_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(mag)));

        unbind();
    }

    void Texture::generateMipMaps()
    {
        bind();

        check_error(glGenerateMipmap(GL_TEXTURE_2D));

        unbind();
    }

    void Texture::bind() const
    {
        check_error(glBindTexture(GL_TEXTURE_2D, id()));
    }

    void Texture::unbind() const
    {
        check_error(glBindTexture(GL_TEXTURE_2D, 0));
    }

    unsigned int Texture::getWidth() const
    {
        return width;
    }

    unsigned int Texture::getHeight() const
    {
        return height;
    }
}}}