#include <ion/wnd/window.hpp>

#include <ion/wnd/context.hpp>
#include <ion/wnd/event.hpp>
#include <ion/log/out.hpp>

#include "window_impl.hpp"

namespace ion { namespace wnd
{
    Window::Window(unsigned int width, unsigned int height, const std::string &title) :
            _impl(WindowImpl::create(width, height, title, event_handlers)),
            _ctx(std::make_unique<Context>(_impl->handle())) {}

    Window::~Window() {}

    void Window::process_events()
    {
        _impl->process_events();
    }

    void Window::on_closed(std::function<void(const Closed &)>&& connection)
    {
        event_handlers.connect(std::move(connection));
    }

    void Window::on_key_pressed(std::function<void(const KeyPressed &)>&& connection)
    {
        event_handlers.connect(std::move(connection));
    }

    void Window::on_key_pressed_repeat(std::function<void(const KeyPressedRepeat &)>&& connection)
    {
        event_handlers.connect(std::move(connection));
    }

    void Window::on_key_released(std::function<void(const KeyReleased &)>&& connection)
    {
        event_handlers.connect(std::move(connection));
    }

    void Window::on_text_entered(std::function<void(const TextEntered &)>&& connection)
    {
        event_handlers.connect(std::move(connection));
    }

    void Window::on_mouse_motion(std::function<void(const MouseMotion &)>&& connection)
    {
        event_handlers.connect(std::move(connection));
    }

    void Window::on_button_pressed(std::function<void(const ButtonPressed &)>&& connection)
    {
        event_handlers.connect(std::move(connection));
    }

    void Window::on_button_released(std::function<void(const ButtonReleased &)>&& connection)
    {
        event_handlers.connect(std::move(connection));
    }

    Context& Window::context() const
    {
        return *_ctx;
    }
}}