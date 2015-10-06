#include <ion/gfx/gl/index_buffer.hpp>

#include "error.hpp"
#include "extensions.h"
#include "map.hpp"

namespace ion { namespace gfx { namespace gl
{
    IndexBuffer::IndexBuffer() : Resource(glGenBuffers, glDeleteBuffers) {}

    IndexBuffer::IndexBuffer(const IndexBuffer& copy) : Resource(copy) {}

    IndexBuffer& IndexBuffer::operator=(const IndexBuffer& copy)
    {
        Resource::operator=(copy);
        return *this;
    }

    void IndexBuffer::data(const void* pointer, int64_t size, BufferUsage usage)
    {
        check_error(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id()));
        check_error(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pointer, map(usage)));
        check_error(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}}}