#pragma once

#include <ion/singleton.hpp>
#include <ion/log/level.hpp>
#include <ion/log/output.hpp>

namespace ion { namespace log
{
    template<typename Level, typename Output>
    inline Output& out()
    {
        return Singleton<Output>::get() << Level::description() << Manipulator::Space;
    }

    template<typename Level>
    inline DefaultOutput& out()
    {
        return out<Level, DefaultOutput>();
    }

    inline DefaultOutput& out()
    {
        return out<DefaultLevel, DefaultOutput>();
    }
}}