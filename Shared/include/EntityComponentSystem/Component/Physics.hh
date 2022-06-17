#pragma once

#include <cstdint>

#include <Physics/Vector.hh>

namespace shared
{
    namespace ecs
    {
        class Entity;
    }

    namespace coder
    {
        class Writer;
    }
}

namespace shared::ecs::component
{
    class Physics
    {
        Entity *entity;

    public:
        physics::Vector position = physics::Vector(0, 0);
        physics::Vector velocity = physics::Vector(0, 0);

        bool updated = false;
        static constexpr uint8_t ID = 1;

        Physics(Entity *);

        void WriteBinary(coder::Writer &writer);
    };
}
