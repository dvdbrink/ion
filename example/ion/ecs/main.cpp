#include <ion/ecs.hpp>

#include <iostream>

struct Position : public ion::ecs::Component<Position>
{
public:
    int x;
    int y;

public:
    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
};

struct Direction : public ion::ecs::Component<Direction>
{
public:
    int x;
    int y;

public:
    Direction() : x(0), y(0) {}
    Direction(int x, int y) : x(x), y(y) {}
};

class MovementSystem : public ion::ecs::System
{
public:
    MovementSystem() : ion::ecs::System(Position(), Direction()) {}

    void update(ion::ecs::Entity::Ptr entity, double dt)
    {
        entity->component<Position>()->x += entity->component<Direction>()->x;
        entity->component<Position>()->y += entity->component<Direction>()->y;
    }
};

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
    return os << "Position { " << pos.x << ", " << pos.y << " }";
}

int main()
{
    ion::ecs::World world;
    world.add<MovementSystem>();

    auto entity = world.create_entity();
    entity->add<Position>(10, 10);
    entity->add<Direction>(2, 1);

    std::cout << *entity->component<Position>() << std::endl;

    world.update(1);

    std::cout << *entity->component<Position>() << std::endl;

    return 0;
}
