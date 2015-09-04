#include "window_impl.hpp"

#include <ion/platform.hpp>
#include <ion/log/out.hpp>

#if defined(ION_PLATFORM_LINUX)
    #include "x11/window_impl.hpp"
#elif defined(ION_PLATFORM_WINDOWS)
    #include "win32/window_impl.hpp"
#endif

namespace ion { namespace wnd
{
    std::unique_ptr<WindowImpl> WindowImpl::create(unsigned int width, unsigned int height, const std::string& title, Events& event_handlers)
    {
        #if defined(ION_PLATFORM_LINUX)
            return std::make_unique<x11::X11WindowImpl>(width, height, title, event_handlers);
        #elif defined(ION_PLATFORM_WINDOWS)
            return std::make_unique<win32::Win32WindowImpl>(width, height, title, event_handlers);
        #endif
    }

    WindowImpl::WindowImpl(unsigned int width, unsigned int height, const std::string& title, Events& event_handlers) :
            _width(width),
            _height(height),
            _title(title),
            event_handlers(event_handlers) {}

    WindowImpl::~WindowImpl() {}

    const WindowHandle& WindowImpl::handle() const
    {
        return _handle;
    }
}}