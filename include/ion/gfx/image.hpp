#pragma once

#include <ion/gfx/pixel_format.hpp>
#include <ion/gfx/type.hpp>

#include <ostream>
#include <vector>

namespace ion { namespace gfx
{
    class Image
    {
    public:
        Image(const std::string&);

        const std::string& name() const;
        unsigned int width() const;
        unsigned int height() const;
        unsigned int channels() const;
        Format format() const;
        Type type() const;
        const std::vector<unsigned char> pixels() const;

    private:
        void load();

    private:
        std::string _name;
        unsigned int _width, _height, _channels;
        std::vector<unsigned char> _data;
    };
}}