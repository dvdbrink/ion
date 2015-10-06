#pragma once

#include <cstdint>

namespace ion { namespace sfx { namespace al
{
    class Buffer;

    class Source
    {
    public:
        Source();
        Source(const Buffer&);
        virtual ~Source();

        void buffer(const Buffer&);

        void play();
        void pause();
        void stop();

    private:
        uint32_t _id;
    };
}}}