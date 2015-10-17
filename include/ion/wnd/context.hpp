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

        void clear();
        void swap_buffers();

        void vertical_sync(bool);
        void clear_color(gfx::Color);

    private:
        std::unique_ptr<ContextImpl> impl;
    };
}}