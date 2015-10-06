#pragma once

#include <ion/log/out.hpp>

#include <string>

#define check_error(call) ((call), ion::sfx::al::check(__FILE__, __LINE__))

namespace ion { namespace sfx { namespace al
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
            return "[OPENAL]";
        }
    };

    void check(const std::string& file, unsigned int line);
}}}