#include <ion/gfx/gl/render_buffer.hpp>

#include "extensions.h"

namespace ion { namespace gfx { namespace gl
{
    RenderBuffer::RenderBuffer() : Resource(glGenRenderbuffers, glDeleteRenderbuffers) {}

    RenderBuffer::RenderBuffer(const RenderBuffer& copy) : Resource(copy) {}

    RenderBuffer& RenderBuffer::operator=(const RenderBuffer& copy)
    {
        Resource::operator=(copy);
        return *this;
    }
}}}