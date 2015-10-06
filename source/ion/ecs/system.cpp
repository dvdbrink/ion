#include <ion/ecs/system.hpp>

namespace ion { namespace ecs
{
    System::~System() {}

    const ComponentMask& System::component_mask() const
    {
        return _component_mask;
    }

    void System::create_component_mask() {}
}}