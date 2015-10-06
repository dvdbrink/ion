#include <ion/sfx/al/context.hpp>

#include <ion/sfx/al/device.hpp>

#include <stdexcept>

#include <al/al.h>
#include <al/alc.h>

namespace ion { namespace sfx { namespace al
{
    Context::Context(const Device& device) : _context(nullptr)
    {
        if (device._device)
        {
            _context = alcCreateContext(device._device, nullptr);
            if (_context)
            {
                alcMakeContextCurrent(_context);
            }
            else
            {
                throw std::runtime_error("Unable to create audio context");
            }
        }
        else
        {
            throw std::runtime_error("Unable to create audio context with invalid device");
        }
    }

    Context::~Context()
    {
        alcMakeContextCurrent(nullptr);
        if (_context)
        {
            alcDestroyContext(_context);
        }
    }
}}}