#pragma once

#include "../handle.hpp"
#include "../context_impl.hpp"

struct HDC__;
struct HGLRC__;

namespace ion { namespace wnd { namespace wgl
{
    typedef HDC__* HDC;
    typedef HGLRC__* HGLRC;

    class WGLContextImpl : public ContextImpl
    {
    public:
        WGLContextImpl(const WindowHandle&);
        ~WGLContextImpl();

        void swap_buffers();
        void vertical_sync(bool);

    private:
        HGLRC renderContext;
        HDC deviceContext;
    };
}}}