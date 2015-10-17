#pragma once

#include <ion/gfx/primitive_type.hpp>
#include <ion/gfx/type.hpp>

#include <cstdint>

namespace ion { namespace gfx { namespace gl
{
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;

    void draw(const VertexArray&, const VertexBuffer&, PrimitiveType, int, int64_t);
    void draw(const VertexArray&, const VertexBuffer&, const IndexBuffer&, PrimitiveType, Type, int);
}}}
