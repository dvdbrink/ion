#include "error.hpp"

#include <al/al.h>
#include <al/alc.h>

namespace ion { namespace sfx { namespace al
{
    void check(const std::string &file, unsigned int line)
    {
        ALenum errorCode(alGetError());

        if (errorCode != AL_NO_ERROR)
        {
            std::string error;

            switch (errorCode) {
                case AL_INVALID_NAME:
                    error = "AL_INVALID_NAME";
                    break;
                case AL_INVALID_ENUM:
                    error = "AL_INVALID_ENUM";
                    break;
                case AL_INVALID_VALUE:
                    error = "AL_INVALID_VALUE";
                    break;
                case AL_INVALID_OPERATION:
                    error = "AL_INVALID_OPERATION";
                    break;
                case AL_OUT_OF_MEMORY:
                    error = "AL_OUT_OF_MEMORY";
                    break;
                default:
                    error = "Unknown error";
            }

            log::out<Error>() << "(" << file << ", " << line << ") " << error << log::Endl;
        }
    }
}}}