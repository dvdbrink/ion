#pragma once

#include <ion/ecs/entity.hpp>
#include <ion/ecs/system.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

namespace ion { namespace ecs
{
    class World
    {
    public:
        World();

        Entity::Ptr create_entity();

        void add(System::Ptr);

        template <typename S, typename...Args>
        void add(Args&&... args)
        {
            add(std::make_shared<S>(std::forward<Args>(args)...));
        }

        void update(double dt);

    private:
        Entity::Id _next_entity_id;
        std::unordered_map<Entity::Id, Entity::Ptr> _entities;
        std::vector<System::Ptr> _systems;
    };
}}