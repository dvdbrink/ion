#pragma once

#include <ion/wnd/keyboard.hpp>
#include <ion/wnd/mouse.hpp>

#include "../window_impl.hpp"

#include <string>

namespace ion { namespace wnd { namespace x11
{
    class X11WindowImpl : public WindowImpl
    {
    public:
        X11WindowImpl(unsigned int width, unsigned int height, const std::string& title, Events&);
        virtual ~X11WindowImpl();

        void process_events();

    private:
        void handle_client_message(const XEvent&);
        void set_title(const std::string&);
        void set_mouse_visible(bool);
        void set_mouse_position(int, int);

        void handle_key_press_event(const XEvent&);
        void handle_key_release_event(XEvent&);
        void handle_mouse_button_press_event(const XEvent&);
        void handle_mouse_button_release_event(const XEvent&);
        void handle_mouse_motion_event(const XEvent&);

        Key key_from_xevent(const XEvent&);
        std::string string_from_xevent(const XEvent&);
        Key map(const KeySym&);
        Button map(const unsigned int);

        int previous_mouse_x;
        int previous_mouse_y;
        Cursor hidden_cursor;
    };
}}}