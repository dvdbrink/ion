#include "window_impl.hpp"

#include <ion/wnd/event.hpp>

#include <X11/Xutil.h>

namespace ion { namespace wnd { namespace x11
{
    static Atom close_event_atom;

    Bool check_event(Display*, XEvent* event, XPointer userData)
    {
        return event->xany.window == reinterpret_cast<Window>(userData);
    }

    X11WindowImpl::X11WindowImpl(unsigned int width, unsigned int height, const std::string& title, Events& event_handlers) :
        WindowImpl(width, height, title, event_handlers),
        previous_mouse_x(0),
        previous_mouse_y(0)
    {
        XSetWindowAttributes attributes;
        attributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

        _handle.display = XOpenDisplay(nullptr);
        _handle.screen = DefaultScreen(_handle.display);
        _handle.window = XCreateWindow(
            _handle.display,
            RootWindow(_handle.display, _handle.screen),
            0, 0,
            width, height,
            0,
            DefaultDepth(_handle.display, _handle.screen),
            InputOutput,
            DefaultVisual(_handle.display, _handle.screen),
            CWEventMask,
            &attributes);

        set_title(title);

        close_event_atom = XInternAtom(_handle.display, "WM_DELETE_WINDOW", false);
        XSetWMProtocols(_handle.display, _handle.window, &close_event_atom, 1);

        XMapWindow(_handle.display, _handle.window);
        XMoveWindow(_handle.display, _handle.window, 0, 0);
        XFlush(_handle.display);

        Pixmap cursor_pixmap = XCreatePixmap(_handle.display, _handle.window, 1, 1, 1);
        GC graphics_context = XCreateGC(_handle.display, cursor_pixmap, 0, NULL);
        XDrawPoint(_handle.display, cursor_pixmap, graphics_context, 0, 0);
        XFreeGC(_handle.display, graphics_context);

        XColor color;
        color.flags = DoRed | DoGreen | DoBlue;
        color.red = color.blue = color.green = 0;
        hidden_cursor = XCreatePixmapCursor(_handle.display, cursor_pixmap, cursor_pixmap, &color, &color, 0, 0);

        XFreePixmap(_handle.display, cursor_pixmap);
    }

    X11WindowImpl::~X11WindowImpl()
    {
        if (hidden_cursor)
        {
            set_mouse_visible(true);
            XFreeCursor(_handle.display, hidden_cursor);
        }

        if (_handle.window)
        {
            XDestroyWindow(_handle.display, _handle.window);
            XFlush(_handle.display);
        }

        if (_handle.display)
        {
            XCloseDisplay(_handle.display);
        }
    }

    void X11WindowImpl::set_title(const std::string &title)
    {
        XStoreName(_handle.display, _handle.window, title.c_str());
    }

    void X11WindowImpl::set_mouse_visible(bool visible)
    {
        XDefineCursor(_handle.display, _handle.window, visible ? None : hidden_cursor);
        XFlush(_handle.display);
    }

    void X11WindowImpl::set_mouse_position(int left, int top)
    {
        XWarpPointer(_handle.display, None, RootWindow(_handle.display, _handle.screen), 0, 0, 0, 0, left, top);
        XFlush(_handle.display);
    }

    void X11WindowImpl::process_events()
    {
        XEvent event;
        while (XCheckIfEvent(_handle.display, &event, &check_event, reinterpret_cast<XPointer>(_handle.window)))
        {
            switch (event.type)
            {
                case ClientMessage: handle_client_message(event);             break;
                case KeyPress:      handle_key_press_event(event);            break;
                case KeyRelease:    handle_key_release_event(event);          break;
                case ButtonPress:   handle_mouse_button_press_event(event);   break;
                case ButtonRelease: handle_mouse_button_release_event(event); break;
                case MotionNotify:  handle_mouse_motion_event(event);         break;
            }
        }
    }

    void X11WindowImpl::handle_client_message(const XEvent &event)
    {
        if (event.xclient.data.l[0] == static_cast<long>(close_event_atom))
        {
            Closed closed;
            event_handlers.signal(closed);
        }
    }

    void X11WindowImpl::handle_key_press_event(const XEvent &event)
    {
        KeyPressed key_pressed;
        key_pressed.key = key_from_xevent(event);
        key_pressed.alt = event.xkey.state & Mod1Mask;
        key_pressed.control = event.xkey.state & ControlMask;
        key_pressed.shift = event.xkey.state & ShiftMask;
        event_handlers.signal(key_pressed);

        TextEntered text_entered;
        text_entered.text = string_from_xevent(event);
        if (text_entered.text[0] >= 32 && text_entered.text[0] < 127)
        {
            event_handlers.signal(text_entered);
        }
    }

    void X11WindowImpl::handle_key_release_event(XEvent &event)
    {
        bool is_retriggered = false;
        if (XEventsQueued(_handle.display, QueuedAfterReading))
        {
            XEvent next_event;
            XPeekEvent(_handle.display, &next_event);
            if (next_event.type == KeyPress && next_event.xkey.time == event.xkey.time && next_event.xkey.keycode == event.xkey.keycode)
            {
                KeyPressedRepeat e;
                e.key = key_from_xevent(event);
                e.alt = event.xkey.state & Mod1Mask;
                e.control = event.xkey.state & ControlMask;
                e.shift = event.xkey.state & ShiftMask;
                event_handlers.signal(e);

                // Delete re-triggered key press event
                XNextEvent(_handle.display, &event);
                is_retriggered = true;
            }
        }
        if (!is_retriggered)
        {
            KeyReleased e;
            e.key = key_from_xevent(event);
            e.alt = event.xkey.state & Mod1Mask;
            e.control = event.xkey.state & ControlMask;
            e.shift = event.xkey.state & ShiftMask;
            event_handlers.signal(e);
        }
    }

    void X11WindowImpl::handle_mouse_button_press_event(const XEvent &event)
    {
        ButtonPressed e;
        e.button = map(event.xbutton.button);
        e.motion.x = event.xmotion.x;
        e.motion.y = event.xmotion.y;
        e.motion.dx = event.xmotion.x - previous_mouse_x;
        e.motion.dy = event.xmotion.y - previous_mouse_y;

        previous_mouse_x = event.xmotion.x;
        previous_mouse_y = event.xmotion.y;

        event_handlers.signal(e);
    }

    void X11WindowImpl::handle_mouse_button_release_event(const XEvent &event)
    {
        ButtonReleased e;
        e.button = map(event.xbutton.button);
        e.motion.x = event.xmotion.x;
        e.motion.y = event.xmotion.y;
        e.motion.dx = event.xmotion.x - previous_mouse_x;
        e.motion.dy = event.xmotion.y - previous_mouse_y;

        previous_mouse_x = event.xmotion.x;
        previous_mouse_y = event.xmotion.y;

        event_handlers.signal(e);
    }

    void X11WindowImpl::handle_mouse_motion_event(const XEvent &event)
    {
        MouseMotion e;
        e.x = event.xmotion.x;
        e.y = event.xmotion.y;
        e.dx = event.xmotion.x - previous_mouse_x;
        e.dy = event.xmotion.y - previous_mouse_y;

        previous_mouse_x = event.xmotion.x;
        previous_mouse_y = event.xmotion.y;

        event_handlers.signal(e);
    }

    Key X11WindowImpl::key_from_xevent(const XEvent &event)
    {
        KeySym symbol;
        static XComposeStatus keyboard;
        XLookupString(const_cast<XKeyEvent*>(&event.xkey), 0, 0, &symbol, &keyboard);
        return map(symbol);
    }

    std::string X11WindowImpl::string_from_xevent(const XEvent &event)
    {
        char buffer[32];
        static XComposeStatus keyboard;
        XLookupString(const_cast<XKeyEvent*>(&event.xkey), buffer, sizeof(buffer), 0, &keyboard);
        return std::string(buffer);
    }

    Key X11WindowImpl::map(const KeySym& key)
    {
        KeySym lower, upper;
        XConvertCase(key, &lower, &upper);

        switch (upper)
        {
            case XK_A: return Key::A;
            case XK_B: return Key::B;
            case XK_C: return Key::C;
            case XK_D: return Key::D;
            case XK_E: return Key::E;
            case XK_F: return Key::F;
            case XK_G: return Key::G;
            case XK_H: return Key::H;
            case XK_I: return Key::I;
            case XK_J: return Key::J;
            case XK_K: return Key::K;
            case XK_L: return Key::L;
            case XK_M: return Key::M;
            case XK_N: return Key::N;
            case XK_O: return Key::O;
            case XK_P: return Key::P;
            case XK_Q: return Key::Q;
            case XK_R: return Key::R;
            case XK_S: return Key::S;
            case XK_T: return Key::T;
            case XK_U: return Key::U;
            case XK_V: return Key::V;
            case XK_W: return Key::W;
            case XK_X: return Key::X;
            case XK_Y: return Key::Y;
            case XK_Z: return Key::Z;

            case XK_Up:   return Key::Up;
            case XK_Down: return Key::Down;

            case XK_dead_grave: return Key::Tilde;
            case XK_Return:     return Key::Enter;
            case XK_KP_Enter:   return Key::Enter;
            case XK_BackSpace:  return Key::Backspace;

            default: return Key::Unknown;
        }
    }

    Button X11WindowImpl::map(const unsigned int button)
    {
        switch (button)
        {
            case 1: return Button::Left;
            case 2: return Button::Middle;
            case 3: return Button::Right;

            default: return Button::Unknown;
        }
    }
}}}