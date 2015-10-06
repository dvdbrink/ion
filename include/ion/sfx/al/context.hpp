#pragma once

#include <al/alc.h>

namespace ion { namespace sfx { namespace al
{
    class Device;

    class Context
    {
    public:
        Context(const Device&);
        virtual ~Context();

    private:
        ALCcontext* _context;
    };
}}}