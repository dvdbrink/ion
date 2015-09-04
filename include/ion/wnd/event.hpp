#pragma once

#include <ion/wnd/keyboard.hpp>
#include <ion/wnd/mouse.hpp>

#include <ostream>

namespace ion { namespace wnd
{
    struct Closed
    {

    };

    struct KeyPressed
    {
        Key key;
        bool alt;
        bool control;
        bool shift;
    };

    struct KeyPressedRepeat
    {
        Key key;
        bool alt;
        bool control;
        bool shift;
    };

    struct KeyReleased
    {
        Key key;
        bool alt;
        bool control;
        bool shift;
    };

    struct TextEntered
    {
        std::string text;
    };

    struct MouseMotion
    {
        int x;
        int y;
        int dx;
        int dy;
    };

    struct ButtonPressed
    {
        Button button;
        MouseMotion motion;
    };

    struct ButtonReleased
    {
        Button button;
        MouseMotion motion;
    };

    inline std::ostream& operator<<(std::ostream& out, const KeyPressed& e)
    {
        return out << "KeyPressed(key=" << e.key << ", alt=" << e.alt << ", control=" << e.control << ", shift=" << e.shift << ")";
    }

    inline std::ostream& operator<<(std::ostream& out, const KeyPressedRepeat& e)
    {
        return out << "KeyPressedRepeat(key=" << e.key << ", alt=" << e.alt << ", control=" << e.control << ", shift=" << e.shift << ")";
    }

    inline std::ostream& operator<<(std::ostream& out, const KeyReleased& e)
    {
        return out << "KeyReleased(key=" << e.key << ", alt=" << e.alt << ", control=" << e.control << ", shift=" << e.shift << ")";
    }

    inline std::ostream& operator<<(std::ostream& out, const TextEntered& e)
    {
        return out << "TextEntered(text=" << e.text << ")";
    }

    inline std::ostream& operator<<(std::ostream& out, const MouseMotion& e)
    {
        return out << "MouseMotion(x=" << e.x << ", y=" << e.y << ", dx=" << e.dx << ", dy=" << e.dy << ")";
    }

    inline std::ostream& operator<<(std::ostream& out, const ButtonPressed& e)
    {
        return out << "ButtonPressed(button=" << e.button << ", motion=" << e.motion << ")";
    }

    inline std::ostream& operator<<(std::ostream& out, const ButtonReleased& e)
    {
        return out << "ButtonReleased(button=" << e.button << ", motion=" << e.motion << ")";
    }
}}