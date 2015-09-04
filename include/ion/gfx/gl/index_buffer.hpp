#pragma once

#include <ion/gfx/buffer_usage.hpp>
#include <ion/gfx/gl/resource.hpp>

namespace ion { namespace gfx { namespace gl
{
    class IndexBuffer :    public Resource<IndexBuffer>
    {
    public:
        IndexBuffer();
        IndexBuffer(const IndexBuffer&);

        IndexBuffer& operator=(const IndexBuffer&);

        void data(const void* pointer, int64_t size, BufferUsage usage);
    };
}}}