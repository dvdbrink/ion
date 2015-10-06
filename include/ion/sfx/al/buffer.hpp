#pragma once

#include <cstdint>

namespace ion { namespace sfx { namespace al
{
    class Sound;

    class Buffer
    {
    public:
        Buffer();
        virtual ~Buffer();

        void write(const Sound&);

    private:
        friend class Source;
        uint32_t _id;
    };
}}}