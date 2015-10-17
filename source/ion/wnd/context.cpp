#include <ion/wnd/context.hpp>

#include "handle.hpp"
#include "context_impl.hpp"

namespace ion { namespace wnd
{
    Context::Context(const WindowHandle& windowHandle)
        : impl(ContextImpl::create(windowHandle)) {}

    Context::~Context() {}

    void Context::swap_buffers()
    {
        impl->swap_buffers();
    }

    void Context::vertical_sync(bool b)
    {
        impl->vertical_sync(b);
    }
}}
