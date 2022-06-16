#pragma once

#include <cstdint>

namespace shared::ecs
{
    class Entity;
}

namespace shared::ecs::component
{
    class Physics
    {
        Entity *entity;

    public:
        bool updated = false;
        static constexpr uint8_t ID = 1;

        Physics(Entity *);
    };
}