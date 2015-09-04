#pragma once

#include <ion/ecs/component.hpp>
#include <ion/ecs/entity.hpp>

namespace ion { namespace ecs
{
    class System
    {
    public:
        using Ptr = std::shared_ptr<System>;
    public:
        System() = delete;

        template <typename... Components>
        System(const Components&... components)
        {
            create_component_mask(components...);
        }

        virtual ~System();

        virtual void update(Entity::Ptr, double dt) = 0;

        const ComponentMask &component_mask() const;

    private:
        ComponentMask _component_mask;

    private:
        void create_component_mask();

        template <typename First, typename... Components>
        void create_component_mask(const First&, const Components&... components)
        {
            _component_mask.set(First::family());
            create_component_mask(components...);
        }
    };
}}