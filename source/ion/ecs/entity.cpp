#include <ion/ecs/entity.hpp>

namespace ion { namespace ecs
{
    Entity::Entity(Id id) : _id(id) {}

    Entity::Id Entity::id() const
    {
        return _id;
    }

    const ComponentMask& Entity::component_mask() const
    {
        return _component_mask;
    }
}}