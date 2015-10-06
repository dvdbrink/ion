#include <ion/sfx/al/buffer.hpp>

#include <ion/sfx/al/sound.hpp>

#include "error.hpp"

#include <al/al.h>
#include <al/alc.h>

namespace ion { namespace sfx { namespace al
{
    Buffer::Buffer() : _id(0)
    {
        check_error(alGenBuffers(1, &_id));
    }

    Buffer::~Buffer()
    {
        if (_id)
        {
            check_error(alDeleteBuffers(1, &_id));
        }
    }

    void Buffer::write(const Sound& sound)
    {
        check_error(alBufferData(_id, AL_FORMAT_STEREO16, &sound.samples().front(), sound.samples().size() * sizeof(int16_t), sound.sample_rate()));
    }
}}}