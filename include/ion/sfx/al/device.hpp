#pragma once

#include <al/alc.h>

namespace ion { namespace sfx { namespace al
{
    class Device
    {
    public:
        Device();
        virtual ~Device();

    private:
        friend class Context;
        ALCdevice* _device;
    };
}}}