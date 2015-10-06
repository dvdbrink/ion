#pragma once

#include <ion/log/out.hpp>

#include <string>

#define check_error(call) ((call), ion::gfx::gl::check(__FILE__, __LINE__))

namespace ion { namespace gfx { namespace gl
{
    class Error
    {
    public:
        static log::Level level()
        {
            return log::Level::Error;
        }

        static const std::string description()
        {
            return "[OPENGL]";
        }
    };

    void check(const std::string& file, unsigned int line);
}}}