#include <ion/gfx/image.hpp>

#include <ion/log/out.hpp>
#include <stb/image.h>

namespace ion { namespace gfx
{
    Image::Image(const std::string& image) :
        _name(image),
        _width(0),
        _height(0),
        _channels(4)
    {
        load();
    }

    const std::string& Image::name() const
    {
        return _name;
    }

    unsigned int Image::width() const
    {
        return _width;
    }

    unsigned int Image::height() const
    {
        return _height;
    }

    unsigned int Image::channels() const
    {
        return _channels;
    }

    Format Image::format() const
    {
        return Format::RGBA;
    }

    Type Image::type() const
    {
        return Type::UnsignedByte;
    }

    const std::vector<unsigned char> Image::pixels() const
    {
        return _data;
    }

    void Image::load()
    {
        int x, y, n;
        unsigned char* pointer = stbi_load(_name.c_str(), &x, &y, &n, static_cast<int>(_channels));

        if (pointer && x && y)
        {
            _width = static_cast<unsigned int>(x);
            _height = static_cast<unsigned int>(y);

            _data.assign(pointer, pointer + (_width * _height * _channels));

            stbi_image_free(pointer);
        }
        else
        {
            log::out<log::Error>() << "Failed to load image " << _name << ". Reason: " << stbi_failure_reason() << log::Endl;
        }
    }
}}