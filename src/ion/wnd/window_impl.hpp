#pragma once

#include <ion/event.hpp>

#include "handle.hpp"

#include <string>
#include <memory>

namespace ion { namespace wnd
{
    struct Closed;
    struct KeyPressed;
    struct KeyPressedRepeat;
    struct KeyReleased;
    struct TextEntered;
    struct MouseMotion;
    struct ButtonPressed;
    struct ButtonReleased;

    using Events = EventsBroadcaster<Closed, KeyPressed, KeyPressedRepeat, KeyReleased, TextEntered, MouseMotion, ButtonPressed, ButtonReleased>;

    class WindowImpl
    {
    public:
        static std::unique_ptr<WindowImpl> create(unsigned int width, unsigned int height, const std::string& title, Events&);

    public:
        WindowImpl(unsigned int width, unsigned int height, const std::string& title, Events&);
        virtual ~WindowImpl();

        virtual void process_events() = 0;

        const WindowHandle& handle() const;

    protected:
        unsigned int _width;
        unsigned int _height;
        std::string _title;

        Events& event_handlers;

        WindowHandle _handle;
    };
}}