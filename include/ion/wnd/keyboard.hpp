#pragma once

#include <ostream>

namespace ion { namespace wnd
{
    enum class Key
    {
        Unknown = 0,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Left,
        Right,
        Up,
        Down,
        Tilde,
        Enter,
        Space,
        Backspace
    };

    inline std::ostream& operator<<(std::ostream& out, const Key& key)
    {
        switch (key)
        {
            case Key::Unknown: return out << "Unknown";
            case Key::A: return out << "A";
            case Key::B: return out << "B";
            case Key::C: return out << "C";
            case Key::D: return out << "D";
            case Key::E: return out << "E";
            case Key::F: return out << "F";
            case Key::G: return out << "G";
            case Key::H: return out << "H";
            case Key::I: return out << "I";
            case Key::J: return out << "J";
            case Key::K: return out << "K";
            case Key::L: return out << "L";
            case Key::M: return out << "M";
            case Key::N: return out << "N";
            case Key::O: return out << "O";
            case Key::P: return out << "P";
            case Key::Q: return out << "Q";
            case Key::R: return out << "R";
            case Key::S: return out << "S";
            case Key::T: return out << "T";
            case Key::U: return out << "U";
            case Key::V: return out << "V";
            case Key::W: return out << "W";
            case Key::X: return out << "X";
            case Key::Y: return out << "Y";
            case Key::Z: return out << "Z";
            case Key::Left: return out << "Left";
            case Key::Right: return out << "Right";
            case Key::Up: return out << "Up";
            case Key::Down: return out << "Down";
            case Key::Tilde: return out << "Tilde";
            case Key::Enter: return out << "Enter";
            case Key::Space: return out << "Space";
            case Key::Backspace: return out << "Backspace";
        }
    }
}}