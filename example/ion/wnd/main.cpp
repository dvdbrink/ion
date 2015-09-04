#include <ion/log/out.hpp>
#include <ion/wnd.hpp>

int main()
{
    bool running = true;

    ion::wnd::Window wnd(800, 600, "ion-gfx-example");
    wnd.on_closed([&](const ion::wnd::Closed&) { running = false; });
    wnd.on_key_pressed([](const ion::wnd::KeyPressed& e) { ion::log::out() << e << ion::log::Endl; });
    wnd.on_key_pressed_repeat([](const ion::wnd::KeyPressedRepeat& e) { ion::log::out() << e << ion::log::Endl; });
    wnd.on_key_released([](const ion::wnd::KeyReleased& e) { ion::log::out() << e << ion::log::Endl; });
    wnd.on_text_entered([](const ion::wnd::TextEntered& e) { ion::log::out() << e << ion::log::Endl; });
    wnd.on_mouse_motion([](const ion::wnd::MouseMotion& e) { ion::log::out() << e << ion::log::Endl; });
    wnd.on_button_pressed([](const ion::wnd::ButtonPressed& e) { ion::log::out() << e << ion::log::Endl; });
    wnd.on_button_released([](const ion::wnd::ButtonReleased& e) { ion::log::out() << e << ion::log::Endl; });

    auto& ctx = wnd.context();
    ctx.vertical_sync(true);

    while (running)
    {
        wnd.process_events();
        ctx.swap_buffers();
    }

    return 0;
}