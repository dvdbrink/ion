#pragma once

#include <iostream>

namespace ion { namespace log
{
    enum Manipulator
    {
        Endl = '\n',
        Tab = '\t',
        Space = ' '
    };

    class ConsoleOutput
    {
    public:
        ConsoleOutput() {}
        virtual ~ConsoleOutput() {}

        ConsoleOutput& operator<<(const Manipulator m)
        {
            *this << static_cast<char>(m);
            return *this;
        }

        template<typename T>
        ConsoleOutput& operator<<(const T& t)
        {
            std::cout << t;
            return *this;
        }
    };

    typedef ConsoleOutput DefaultOutput;
}}