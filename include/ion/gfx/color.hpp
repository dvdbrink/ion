#pragma once

namespace ion { namespace gfx
{
    class Color
    {
    public:
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color CornflowerBlue;

    public:
        float r, g, b, a;

    public:
        Color(float r, float g, float b, float a);
    };
}}