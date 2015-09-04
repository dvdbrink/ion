#include <ion/gfx/gl/vertex_buffer.hpp>

#include "error.hpp"
#include "extensions.h"
#include "map.hpp"

namespace ion { namespace gfx { namespace gl
{
    VertexBuffer::VertexBuffer() : Resource(glGenBuffers, glDeleteBuffers) {}

    VertexBuffer::VertexBuffer(const VertexBuffer& copy) : Resource(copy) {}

    VertexBuffer& VertexBuffer::operator=(const VertexBuffer& copy)
    {
        Resource::operator=(copy);
        return *this;
    }

    void VertexBuffer::data(const void* pointer, int64_t size, BufferUsage usage)
    {
        check_error(glBindBuffer(GL_ARRAY_BUFFER, id()));
        check_error(glBufferData(GL_ARRAY_BUFFER, size, pointer, map(usage)));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}}}