#include <ion/sfx/al/device.hpp>

#include <stdexcept>

#include <al/al.h>
#include <al/alc.h>

namespace ion { namespace sfx { namespace al
{
    Device::Device() : _device(nullptr)
    {
        _device = alcOpenDevice(nullptr);
        if (!_device)
        {
            throw std::runtime_error("Unable to open audio device");
        }
    }

    Device::~Device()
    {
        if (_device)
        {
            alcCloseDevice(_device);
        }
    }
}}}