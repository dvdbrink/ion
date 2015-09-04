#include <ion/gfx/gl/vertex_array.hpp>

#include <ion/gfx/gl/vertex_buffer.hpp>
#include <ion/gfx/gl/index_buffer.hpp>

#include "error.hpp"
#include "extensions.h"
#include "map.hpp"

#include <cassert>

namespace ion { namespace gfx { namespace gl
{
    VertexArray::VertexArray() : Resource(glGenVertexArrays, glDeleteVertexArrays) {}

    VertexArray::VertexArray(const VertexArray& copy) : Resource(copy) {}

    VertexArray& VertexArray::operator=(const VertexArray& copy)
    {
        Resource::operator=(copy);
        return *this;
    }

    void VertexArray::attribute(const VertexBuffer& vb, const Attribute& attribute)
    {
        check_error(glBindVertexArray(id()));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, vb.id()));
        check_error(glVertexAttribPointer(attribute.index, attribute.size, map(attribute.type), GL_FALSE, attribute.stride, reinterpret_cast<const GLvoid *>(attribute.offset)));
        check_error(glEnableVertexAttribArray(attribute.index));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, 0));
        check_error(glBindVertexArray(0));
    }

    void VertexArray::draw(const VertexBuffer& vb, PrimitiveType mode, int first, int64_t count)
    {
        check_error(glBindVertexArray(id()));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, vb.id()));
        check_error(glDrawArrays(map(mode), first, count));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, 0));
        check_error(glBindVertexArray(0));
    }

    void VertexArray::draw(const VertexBuffer& vb, const IndexBuffer& ib, PrimitiveType mode, Type type, int count)
    {
        assert(type == Type::UnsignedByte || type == Type::UnsignedShort || type == Type::UnsignedInt);
        check_error(glBindVertexArray(id()));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, vb.id()));
        check_error(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.id()));
        check_error(glDrawElements(map(mode), count, map(type), nullptr));
        check_error(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, 0));
        check_error(glBindVertexArray(0));
    }
}}}