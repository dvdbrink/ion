#pragma once

#include <bitset>

namespace ion { namespace ecs
{
    using ComponentMask = std::bitset<32>;

    struct BaseComponent
    {
    public:
        typedef uint64_t Family;

    protected:
        static Family next_family;
    };

    template <typename Derived>
    struct Component : public BaseComponent
    {
    public:
        static Family family()
        {
            static Family family = next_family++;
            return family;
        }
    };
}}