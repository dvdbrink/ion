#pragma once

#include "../handle.hpp"
#include "../context_impl.hpp"

struct __GLXcontextRec;

namespace ion { namespace wnd { namespace glx
{
    typedef __GLXcontextRec* GLXContext;

    class GLXContextImpl : public ContextImpl
    {
    public:
        GLXContextImpl(const WindowHandle&);
        ~GLXContextImpl();

        void swap_buffers();
        void vertical_sync(bool);

    private:
        GLXContext context;
    };
}}}