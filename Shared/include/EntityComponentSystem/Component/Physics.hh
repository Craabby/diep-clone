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
        class Reader;
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

        void Tick();

        bool updated = false;
        static constexpr uint8_t ID = 2;

        Physics(Entity *);

        void WriteBinary(coder::Writer &writer);
        void FromBinary(coder::Reader &reader);
    };
}
