#pragma once

#include <array>
#include <map>
#include <string>

struct stbtt_fontinfo;

namespace ion { namespace gfx
{
    template <typename T>
    struct Point
    {
        T x;
        T y;
    };

    template <typename T>
    struct Rect
    {
        T left;
        T top;
        T right;
        T bottom;
        T width;
        T height;
    };

    struct Glyph
    {
        Point<float> offset;
        Rect<int> rect;
        Point<int> advance;
    };

    class Font
    {
    public:
        Font(const std::string& font, const uint32_t size);
        virtual ~Font();

        const Glyph& glyph(const uint32_t character) const;

    private:
        std::vector<char> load_file();
        stbtt_fontinfo init_font(const std::vector<char>&);
        void load_glyphs(const stbtt_fontinfo&);
        void load_glyph(const stbtt_fontinfo&, const Glyph&);

    private:
        static std::array<uint32_t, 96> charset;
        std::map<uint32_t, Glyph> glyphs;
    };
}}