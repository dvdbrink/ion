#pragma once

#include <ion/event.hpp>

#include <string>
#include <memory>
#include "event.hpp"

namespace ion { namespace wnd
{
    class WindowImpl;
    class Context;

    struct Closed;
    struct KeyPressed;
    struct KeyPressedRepeat;
    struct KeyReleased;
    struct TextEntered;
    struct MouseMotion;
    struct ButtonPressed;
    struct ButtonReleased;

    using Events = EventsBroadcaster<Closed, KeyPressed, KeyPressedRepeat, KeyReleased, TextEntered, MouseMotion, ButtonPressed, ButtonReleased>;

    class Window
    {
    public:
        Window(unsigned int width, unsigned int height, const std::string& title);
        virtual ~Window();

        void process_events();

        void on_closed(std::function<void(const Closed&)>&&);
        void on_key_pressed(std::function<void(const KeyPressed&)>&&);
        void on_key_pressed_repeat(std::function<void(const KeyPressedRepeat&)>&&);
        void on_key_released(std::function<void(const KeyReleased&)>&&);
        void on_text_entered(std::function<void(const TextEntered&)>&&);
        void on_mouse_motion(std::function<void(const MouseMotion&)>&&);
        void on_button_pressed(std::function<void(const ButtonPressed&)>&&);
        void on_button_released(std::function<void(const ButtonReleased&)>&&);

        Context& context() const;

    private:
        std::unique_ptr<WindowImpl> _impl;
        std::unique_ptr<Context> _ctx;

        Events event_handlers;
    };
}}