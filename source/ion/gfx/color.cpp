#include <ion/gfx/color.hpp>

namespace ion { namespace gfx
{
    Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    const Color Color::White = {1.0f, 1.0f, 1.0f, 1.0f};
    const Color Color::Black = {.0f, .0f, .0f, 1.0f};
    const Color Color::Red = {1.0f, .0f, .0f, 1.0f};
    const Color Color::Green = {.0f, 1.0f, .0f, 1.0f};
    const Color Color::Blue = {.0f, .0f, 1.0f, 1.0f};
    const Color Color::CornflowerBlue = {0.4f, 0.6f, 0.9f, 0.0f};
}}