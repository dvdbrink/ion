#pragma once

#include <string>

namespace ion { namespace log
{
    enum class Level
    {
        Debug,
        Error,
        Fatal,
        Info,
        Trace,
        Warn
    };

    class Debug
    {
    public:
        static Level level()
        {
            return Level::Debug;
        }

        static const std::string description()
        {
            return "[DEBUG]";
        }
    };

    class Error
    {
    public:
        static Level level()
        {
            return Level::Error;
        }

        static const std::string description()
        {
            return "[ERROR]";
        }
    };

    class Fatal
    {
    public:
        static Level level()
        {
            return Level::Fatal;
        }

        static const std::string description()
        {
            return "[FATAL]";
        }
    };

    class Info
    {
    public:
        static Level level()
        {
            return Level::Info;
        }

        static const std::string description()
        {
            return "[INFO]";
        }
    };

    class Trace
    {
    public:
        static Level level()
        {
            return Level::Trace;
        }

        static const std::string description()
        {
            return "[TRACE]";
        }
    };

    class Warn
    {
    public:
        static Level level()
        {
            return Level::Warn;
        }

        static const std::string description()
        {
            return "[WARN]";
        }
    };

    typedef Debug DefaultLevel;
}}