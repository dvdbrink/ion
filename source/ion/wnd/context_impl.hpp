#pragma once

#include <ion/gfx/color.hpp>

#include "handle.hpp"

#include <memory>

namespace ion { namespace wnd
{
    class ContextImpl
    {
    public:
        static std::unique_ptr<ContextImpl> create(const WindowHandle&);

    public:
        ContextImpl(const WindowHandle&);
        virtual ~ContextImpl();

        virtual void swap_buffers() = 0;
        virtual void vertical_sync(bool) = 0;

    protected:
        WindowHandle _handle;
    };
}}