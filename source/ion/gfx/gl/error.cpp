#include "error.hpp"

#include "extensions.h"

namespace ion { namespace gfx { namespace gl
{
    void check(const std::string &file, unsigned int line)
    {
        GLenum errorCode(glGetError());

        if (errorCode != GL_NO_ERROR)
        {
            std::string error;

            switch (errorCode) {
                case GL_INVALID_ENUM:
                    error = "GL_INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    error = "GL_INVALID_VALUE";
                    break;
                case GL_INVALID_OPERATION:
                    error = "GL_INVALID_OPERATION";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    error = "GL_INVALID_FRAMEBUFFER_OPERATION";
                    break;
                case GL_OUT_OF_MEMORY:
                    error = "GL_OUT_OF_MEMORY";
                    break;
                default:
                    error = "Unknown error";
            }

            log::out<Error>() << "(" << file << ", " << line << ") " << error << log::Endl;
        }
    }
}}}