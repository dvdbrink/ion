#pragma once

#include <ion/gfx/gl/resource.hpp>

namespace ion { namespace gfx { namespace gl
{
    class FrameBuffer : public Resource<FrameBuffer>
    {
    public:
        FrameBuffer();
        FrameBuffer(const FrameBuffer&);

        FrameBuffer& operator=(const FrameBuffer&);

        void bind();
        void unbind();
    };
}}}