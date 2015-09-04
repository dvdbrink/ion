#pragma once

namespace ion { namespace wnd
{
    enum class Button
    {
        Unknown,
        Left,
        Middle,
        Right
    };

    inline std::ostream& operator<<(std::ostream& out, const Button& button)
    {
        switch (button)
        {
            case Button::Unknown: return out << "Unknown";
            case Button::Left: return out << "Left";
            case Button::Middle: return out << "Middle";
            case Button::Right: return out << "Right";
        }
    }
}}