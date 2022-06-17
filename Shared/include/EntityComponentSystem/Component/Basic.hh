#pragma once

#include <cstdint>

namespace shared::ecs
{
    class Entity;
}

namespace shared::ecs::component
{
    class Basic
    {
        Entity *entity;

    public:
        bool updated = false;
        static constexpr uint8_t ID = 0;

        Basic(Entity *);
    };
}