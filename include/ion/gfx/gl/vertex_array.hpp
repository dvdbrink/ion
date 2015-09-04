#pragma once

#include <ion/gfx/primitive_type.hpp>
#include <ion/gfx/type.hpp>
#include <ion/gfx/gl/resource.hpp>

namespace ion { namespace gfx { namespace gl
{
    class VertexBuffer;
    class IndexBuffer;

    struct Attribute
    {
        unsigned int index;
        int size;
        Type type;
        int stride;
        unsigned int offset;
    };

    class VertexArray : public Resource<VertexArray>
    {
    public:
        VertexArray();
        VertexArray(const VertexArray&);

        VertexArray& operator=(const VertexArray&);

        void attribute(const VertexBuffer&, const Attribute&);

        void draw(const VertexBuffer&, PrimitiveType, int, int64_t);
        void draw(const VertexBuffer&, const IndexBuffer&, PrimitiveType, Type, int);
    };
}}}