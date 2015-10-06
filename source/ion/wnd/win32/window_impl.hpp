#pragma once

#include "../window_impl.hpp"

#include <ion/wnd/keyboard.hpp>

#include <windows.h>

struct RAWINPUTDEVICE__
{
    USHORT usUsagePage;
    USHORT usUsage;
    DWORD  dwFlags;
    HWND   hwndTarget;
};

namespace ion { namespace wnd { namespace win32
{
    typedef RAWINPUTDEVICE__ RAWINPUTDEVICE;

    class Win32WindowImpl : public WindowImpl
    {
    public:
        Win32WindowImpl(unsigned int width, unsigned int height, const std::string& title, Events&);
        virtual ~Win32WindowImpl();

        void process_events();

    private:
        RAWINPUTDEVICE rid[2];
        long mouse_position_x, mouse_position_y;

        static const std::string CLASS_NAME;
        static LRESULT CALLBACK on_event(HWND handle, uint32_t message, WPARAM wParam, LPARAM lParam);

    private:
        bool register_class();
        bool create_window();
        void show_window();
        void destroy_window();
        void unregister_class();
        LRESULT CALLBACK process_event(uint32_t message, WPARAM wParam, LPARAM lParam);
        void handle_close_event();

        void register_input_devices();

        void handle_input_event(LPARAM param);

        Key map(unsigned short key_code);

        std::string map(const Key &key);

        void set_title(std::string const &title);

        void set_mouse_visible(bool visible);

        void set_mouse_position(int left, int top);
    };
}}}