#pragma once

#include <ion/gfx/gl/resource.hpp>

namespace ion { namespace gfx { namespace gl
{
    class RenderBuffer : public Resource<RenderBuffer>
    {
    public:
        RenderBuffer();
        RenderBuffer(const RenderBuffer&);

        RenderBuffer& operator=(const RenderBuffer&);
    };
}}}