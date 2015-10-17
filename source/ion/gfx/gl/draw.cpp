#include <ion/gfx/gl/draw.hpp>

#include <ion/gfx/gl/vertex_array.hpp>
#include <ion/gfx/gl/vertex_buffer.hpp>
#include <ion/gfx/gl/index_buffer.hpp>

#include "error.hpp"
#include "extensions.h"
#include "map.hpp"

#include <cassert>

namespace ion { namespace gfx { namespace gl
{
    void draw(const VertexArray& va, const VertexBuffer& vb, PrimitiveType mode, int first, int64_t count)
    {
        check_error(glBindVertexArray(va.id()));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, vb.id()));
        check_error(glDrawArrays(map(mode), first, count));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, 0));
        check_error(glBindVertexArray(0));
    }

    void draw(const VertexArray& va, const VertexBuffer& vb, const IndexBuffer& ib, PrimitiveType mode, Type type, int count)
    {
        assert(type == Type::UnsignedByte || type == Type::UnsignedShort || type == Type::UnsignedInt);
        check_error(glBindVertexArray(va.id()));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, vb.id()));
        check_error(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.id()));
        check_error(glDrawElements(map(mode), count, map(type), nullptr));
        check_error(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        check_error(glBindBuffer(GL_ARRAY_BUFFER, 0));
        check_error(glBindVertexArray(0));
    }
}}}
