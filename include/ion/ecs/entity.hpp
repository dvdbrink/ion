#pragma once

#include <ion/ecs/component.hpp>

#include <memory>
#include <stdexcept>
#include <unordered_map>

namespace ion { namespace ecs
{
    using ComponentMap = std::unordered_map<BaseComponent::Family, std::shared_ptr<BaseComponent>>;

    class Entity
    {
    public:
        using Id = uint64_t;
        using Ptr = std::shared_ptr<Entity>;

    public:
        template <typename C>
        void add(std::shared_ptr<C> component)
        {
            _components.insert(std::make_pair(C::family(), component));
            _component_mask.set(C::family());
        }

        template <typename C, typename... Args>
        void add(Args&&... args)
        {
            add(std::make_shared<C>(std::forward<Args>(args)...));
        }

        template <typename C>
        std::shared_ptr<C> component()
        {
            if (!_component_mask.test(C::family()))
            {
                throw std::runtime_error("No such component");
            }
            auto base = _components.at(C::family());
            return std::static_pointer_cast<C>(base);
        }

        Id id() const;

        const ComponentMask& component_mask() const;

    private:
        Id _id;
        ComponentMap _components;
        ComponentMask _component_mask;

    private:
        friend class World;
        Entity(Id id);
    };
}}