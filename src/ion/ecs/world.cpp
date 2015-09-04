#include <ion/ecs/world.hpp>

namespace ion { namespace ecs
{
    World::World() : _next_entity_id(0) {}

    Entity::Ptr World::create_entity()
    {
        Entity::Id id = _next_entity_id;
        auto entity = Entity::Ptr(new Entity(id));
        _entities.insert(std::make_pair(id, entity));
        return entity;
    }

    void World::add(System::Ptr system)
    {
        _systems.push_back(system);
    }

    void World::update(double dt)
    {
        for (auto entity : _entities)
        {
            for (auto system : _systems)
            {
                if ((entity.second->component_mask() & system->component_mask()) == system->component_mask())
                {
                    system->update(entity.second, dt);
                }
            }
        }
    }
}}