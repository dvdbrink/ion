#include "window_impl.hpp"

#include <ion/log/out.hpp>
#include <ion/wnd/event.hpp>

namespace ion { namespace wnd { namespace win32
{
    const std::string Win32WindowImpl::CLASS_NAME = "Win32WindowImpl";

    Win32WindowImpl::Win32WindowImpl(unsigned int width, unsigned int height, const std::string& title, Events& event_handlers)
            : WindowImpl(width, height, title, event_handlers),
              mouse_position_x(0), mouse_position_y(0)
    {
        if (register_class())
        {
            if (create_window())
            {
                show_window();
                register_input_devices();
            }
            else
            {
                log::out<log::Error>() << "Failed to create window" << log::Endl;
            }
        }
        else
        {
            log::out<log::Error>() << "Failed to register window class" << log::Endl;
        }
    }

    Win32WindowImpl::~Win32WindowImpl()
    {
        destroy_window();
        unregister_class();
    }

    void Win32WindowImpl::set_title(const std::string &title)
    {
        SetWindowText(_handle.hwnd, title.c_str());
    }

    void Win32WindowImpl::set_mouse_visible(bool visible)
    {
        ShowCursor(visible);
    }

    void Win32WindowImpl::set_mouse_position(int left, int top)
    {
        SetCursorPos(left, top);
    }

    void Win32WindowImpl::process_events()
    {
        MSG message;
        while (PeekMessage(&message, _handle.hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    bool Win32WindowImpl::register_class()
    {
        WNDCLASS window;
        window.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        window.lpfnWndProc   = &Win32WindowImpl::on_event;
        window.cbClsExtra    = 0;
        window.cbWndExtra    = 0;
        window.hInstance     = GetModuleHandle(nullptr);
        window.hIcon         = nullptr;
        window.hCursor       = LoadCursor(NULL, IDC_ARROW);;
        window.hbrBackground = nullptr;
        window.lpszMenuName  = nullptr;
        window.lpszClassName = CLASS_NAME.c_str();

        return RegisterClass(&window) != 0;
    }

    bool Win32WindowImpl::create_window()
    {
        _handle.hwnd = CreateWindow(
                CLASS_NAME.c_str(), _title.c_str(),
                WS_OVERLAPPEDWINDOW,
                0, 0, _width, _height,
                nullptr, nullptr,
                GetModuleHandle(nullptr),
                this);

        return _handle.hwnd != nullptr;
    }

    void Win32WindowImpl::show_window()
    {
        ShowWindow(_handle.hwnd, SW_SHOW);
    }

    void Win32WindowImpl::destroy_window()
    {
        DestroyWindow(_handle.hwnd);
    }

    void Win32WindowImpl::unregister_class()
    {
        UnregisterClass(CLASS_NAME.c_str(), GetModuleHandle(nullptr));
    }

    LRESULT CALLBACK Win32WindowImpl::process_event(uint32_t message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
            case WM_DESTROY: handle_close_event();       break;
            case WM_INPUT:   handle_input_event(lParam); break;
        }

        return DefWindowProc(this->_handle.hwnd, message, wParam, lParam);
    }

    void Win32WindowImpl::handle_close_event()
    {
        PostQuitMessage(0);
        Closed closed;
        event_handlers.signal(closed);
    }

    LRESULT CALLBACK Win32WindowImpl::on_event(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam)
    {
        Win32WindowImpl* window;

        if (message == WM_NCCREATE)
        {
            window = reinterpret_cast<Win32WindowImpl*>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
            window->_handle.hwnd = hwnd;
        }
        else
        {
            window = reinterpret_cast<Win32WindowImpl*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (window)
        {
            return window->process_event(message, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    void Win32WindowImpl::register_input_devices()
    {
        rid[0].usUsagePage = 1;
        rid[0].usUsage = 2;
        rid[0].dwFlags = 0;
        rid[0].hwndTarget = nullptr;

        rid[1].usUsagePage = 1;
        rid[1].usUsage = 6;
        rid[1].dwFlags = 0;
        rid[1].hwndTarget = nullptr;

        if (RegisterRawInputDevices((PCRAWINPUTDEVICE)rid, 2, sizeof(rid[0])) == FALSE)
        {
            log::out<log::Error>() << "RegisterRawInputDevices failed. (" << GetLastError() << ")" << log::Endl;
        }
    }

    void Win32WindowImpl::handle_input_event(LPARAM lParam)
    {
        unsigned int buffer_size;
        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &buffer_size, sizeof(RAWINPUTHEADER));
        BYTE *buffer = new BYTE[buffer_size];
        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, (LPVOID)buffer, &buffer_size, sizeof(RAWINPUTHEADER));

        RAWINPUT *raw = (RAWINPUT*) buffer;
        if (raw->header.dwType == RIM_TYPEKEYBOARD)
        {
            USHORT key_code = raw->data.keyboard.VKey;
            bool key_up = raw->data.keyboard.Flags & RI_KEY_BREAK;

            Key key = map(key_code);
            if (key_up)
            {
                KeyReleased e;
                e.key = key;
                e.alt = HIWORD(GetAsyncKeyState(VK_MENU))!=0;
                e.control = HIWORD(GetAsyncKeyState(VK_CONTROL))!=0;
                e.shift = HIWORD(GetAsyncKeyState(VK_SHIFT))!=0;
                event_handlers.signal(e);
            }
            else
            {
                KeyPressed e;
                e.key = key;
                e.alt = HIWORD(GetAsyncKeyState(VK_MENU))!=0;
                e.control = HIWORD(GetAsyncKeyState(VK_CONTROL))!=0;
                e.shift = HIWORD(GetAsyncKeyState(VK_SHIFT))!=0;
                event_handlers.signal(e);
            }

            std::string str = map(key);
            if (key_up && str.size() > 0)
            {
                TextEntered e;
                e.text = str;
                event_handlers.signal(e);
            }
        }
        if (raw->header.dwType == RIM_TYPEMOUSE)
        {
            long mouse_motion_x = raw->data.mouse.lLastX;
            long mouse_motion_y = raw->data.mouse.lLastY;
            if (mouse_motion_x != 0 || mouse_motion_y != 0)
            {
                mouse_position_x += mouse_motion_x;
                mouse_position_y += mouse_motion_y;

                MouseMotion e;
                e.x = mouse_position_x;
                e.y = mouse_position_y;
                e.dx = mouse_motion_x;
                e.dy = mouse_motion_y;
                event_handlers.signal(e);
            }

            if (raw->data.mouse.ulButtons & RI_MOUSE_LEFT_BUTTON_UP)
            {
                ButtonReleased e;
                e.button = Button::Left;
                event_handlers.signal(e);
            }
            if (raw->data.mouse.ulButtons & RI_MOUSE_LEFT_BUTTON_DOWN)
            {
                ButtonPressed e;
                e.button = Button::Left;
                event_handlers.signal(e);
            }
            if (raw->data.mouse.ulButtons & RI_MOUSE_MIDDLE_BUTTON_UP)
            {
                ButtonReleased e;
                e.button = Button::Middle;
                event_handlers.signal(e);
            }
            if (raw->data.mouse.ulButtons & RI_MOUSE_MIDDLE_BUTTON_DOWN)
            {
                ButtonPressed e;
                e.button = Button::Middle;
                event_handlers.signal(e);
            }
            if (raw->data.mouse.ulButtons & RI_MOUSE_RIGHT_BUTTON_UP)
            {
                ButtonReleased e;
                e.button = Button::Right;
                event_handlers.signal(e);
            }
            if (raw->data.mouse.ulButtons & RI_MOUSE_RIGHT_BUTTON_DOWN)
            {
                ButtonPressed e;
                e.button = Button::Right;
                event_handlers.signal(e);
            }
        }

        delete[] buffer;
    }

    Key Win32WindowImpl::map(unsigned short key_code)
    {
        switch (key_code)
        {
            case 'A': return Key::A;
            case 'B': return Key::B;
            case 'C': return Key::C;
            case 'D': return Key::D;
            case 'E': return Key::E;
            case 'F': return Key::F;
            case 'G': return Key::G;
            case 'H': return Key::H;
            case 'I': return Key::I;
            case 'J': return Key::J;
            case 'K': return Key::K;
            case 'L': return Key::L;
            case 'M': return Key::M;
            case 'N': return Key::N;
            case 'O': return Key::O;
            case 'P': return Key::P;
            case 'Q': return Key::Q;
            case 'R': return Key::R;
            case 'S': return Key::S;
            case 'T': return Key::T;
            case 'U': return Key::U;
            case 'V': return Key::V;
            case 'W': return Key::W;
            case 'X': return Key::X;
            case 'Y': return Key::Y;
            case 'Z': return Key::Z;

            case VK_UP:   	return Key::Up;
            case VK_DOWN: 	return Key::Down;
            case VK_LEFT:	return Key::Left;
            case VK_RIGHT:  return Key::Right;

            case VK_OEM_3: return Key::Tilde;

            default: return Key::Unknown;
        }
    }

    std::string Win32WindowImpl::map(const Key& key)
    {
        switch (key)
        {
            case Key::A: return "a";
            case Key::B: return "b";
            case Key::C: return "c";
            case Key::D: return "d";
            case Key::E: return "e";
            case Key::F: return "f";
            case Key::G: return "g";
            case Key::H: return "h";
            case Key::I: return "i";
            case Key::J: return "j";
            case Key::K: return "k";
            case Key::L: return "l";
            case Key::M: return "m";
            case Key::N: return "n";
            case Key::O: return "o";
            case Key::P: return "p";
            case Key::Q: return "q";
            case Key::R: return "r";
            case Key::S: return "s";
            case Key::T: return "t";
            case Key::U: return "u";
            case Key::V: return "v";
            case Key::W: return "w";
            case Key::X: return "x";
            case Key::Y: return "y";
            case Key::Z: return "z";

            case Key::Space: return " ";
            case Key::Tilde: return "~";

            default: return "";
        }
    }
}}}