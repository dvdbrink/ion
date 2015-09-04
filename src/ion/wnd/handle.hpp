#pragma once

#include <ion/platform.hpp>

#if defined(ION_PLATFORM_LINUX)
    #include <X11/Xlib.h>
#elif defined(ION_PLATFORM_WINDOWS)
    struct HWND__;
#endif

namespace ion { namespace wnd
{
    #if defined(ION_PLATFORM_LINUX)
        struct WindowHandle
        {
            unsigned long window;
            int screen;
            ::Display* display;
        };
    #elif defined(ION_PLATFORM_WINDOWS)
        struct WindowHandle
        {
            HWND__* hwnd;
        };
    #endif
}}