#include <ion/sfx/al/source.hpp>

#include <ion/sfx/al/buffer.hpp>

#include "error.hpp"

#include <al/al.h>
#include <al/alc.h>

namespace ion { namespace sfx { namespace al
{
    Source::Source() : _id(0)
    {
        check_error(alGenSources(1, &_id));
    }

    Source::Source(const Buffer& buf) :
        Source()
    {
        buffer(buf);
    }

    Source::~Source()
    {
        stop();
        if (_id)
        {
            check_error(alDeleteSources(1, &_id));
        }
    }

    void Source::buffer(const Buffer& buffer)
    {
        check_error(alSourcei(_id, AL_BUFFER, buffer._id));
    }

    void Source::play()
    {
        check_error(alSourcePlay(_id));
    }

    void Source::pause()
    {
        check_error(alSourcePause(_id));
    }

    void Source::stop()
    {
        check_error(alSourceStop(_id));
    }
}}}