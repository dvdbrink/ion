#pragma once

#include <ion/gfx/buffer_usage.hpp>
#include <ion/gfx/gl/resource.hpp>

namespace ion { namespace gfx { namespace gl
{
    class VertexBuffer : public Resource<VertexBuffer>
    {
    public:
        VertexBuffer();
        VertexBuffer(const VertexBuffer&);

        VertexBuffer& operator=(const VertexBuffer&);

        void data(const void* pointer, int64_t size, BufferUsage usage);
    };
}}}