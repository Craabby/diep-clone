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

        class PhysicsVector : public physics::Vector
        {
            Physics *physicsComponent;

        public:
            PhysicsVector(Physics *physicsComponent, float, float);
            void X(float x);
            void Y(float y);
            float X();
            float Y();
        };

    public:
        physics::Vector position = PhysicsVector(this, 0, 0);
        physics::Vector velocity = PhysicsVector(this, 0, 0);

        void Tick();

        bool updated = false;
        static constexpr uint8_t ID = 3;

        Physics(Entity *);

        void WriteBinary(coder::Writer &writer);
        void FromBinary(coder::Reader &reader);
    };
}
