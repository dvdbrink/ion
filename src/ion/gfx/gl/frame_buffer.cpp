#include <ion/gfx/gl/frame_buffer.hpp>

#include "error.hpp"
#include "extensions.h"

namespace ion { namespace gfx { namespace gl
{
    FrameBuffer::FrameBuffer() : Resource(glGenFramebuffers, glDeleteFramebuffers) {}

    FrameBuffer::FrameBuffer(const FrameBuffer& copy) : Resource(copy) {}

    FrameBuffer& FrameBuffer::operator=(const FrameBuffer& copy)
    {
        Resource::operator=(copy);
        return *this;
    }

    void FrameBuffer::bind()
    {
        check_error(glBindFramebuffer(GL_FRAMEBUFFER, id()));
    }

    void FrameBuffer::unbind()
    {
        check_error(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }
}}}