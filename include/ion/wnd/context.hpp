#pragma once

#include <ion/gfx/color.hpp>

#include <memory>

namespace ion { namespace wnd
{
    struct WindowHandle;
    class ContextImpl;

    class Context
    {
    public:
        Context(const WindowHandle&);
        ~Context();

        void swap_buffers();
        void vertical_sync(bool);

    private:
        std::unique_ptr<ContextImpl> impl;
    };
}}