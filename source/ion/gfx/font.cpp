#include <ion/gfx/font.hpp>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/truetype.h>

#include <fstream>

namespace ion { namespace gfx
{
    std::array<uint32_t, 96> Font::charset = {{
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
    }};

    Font::Font(const std::string& file_name, const uint32_t size)
    {
        auto file_data = load_file(file_name);
        auto font_info = init_font(file_data);
        load_glyphs(font_info);
    }

    const Glyph& Font::glyph(const uint32_t character) const
    {
        return glyphs.at(character);
    }

    std::vector<char> Font::load_file(const std::string& file_name)
    {
        std::ifstream file(file_name, std::ios::binary);

        file.seekg(0, std::ios::end);
        auto file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> data(file_size);
        file.read(&data.front(), file_size);

        return data;
    }

    stbtt_fontinfo init_font(const std::vector<char>& font_data)
    {
        stbtt_fontinfo font_info;
        if (!stbtt_InitFont(&fontInfo, reinterpret_cast<const unsigned char*>(&font_data.front()), 0))
        {
            // fail
        }
        return font_info;
    }

    void Font::load_glyphs(const stbtt_fontinfo& font_info)
    {
        for (const auto character : charset)
        {
            Glyph glyph;
            load_glyph(glyph);
            glyphs.insert(std::make_pair(character, glyph));
        }
    }

    void load_glyph(const stbtt_fontinfo& font_info, const Glyph& glyph)
    {
        stbtt_GetCodepointHMetrics(&font_info, character, &glyph.advance.x, 0);
        stbtt_GetCodepointBitmapBox(&font_info, character, scale, scale, &glyph.rect.left, &glyph.rect.top, &glyph.rect.right, &glyph.rect.bottom);
        unsigned char* bitmap = stbtt_GetCodepointBitmap(&font_info, scale, scale, character, &glyph.rect.width, &glyph.rect.height, 0, 0);
        stbtt_FreeBitmap(bitmap, 0);

        glyph.offset.x = xOffset / static_cast<float>(texture.getWidth());
        glyph.offset.y = yOffset / static_cast<float>(texture.getHeight());
        glyph.advance.x = static_cast<int>(glyph.advance.x * scale);
    }
}}