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
    class Camera
    {
        Entity *entity;
        int32_t playerId;

    public:
        struct Inputs
        {
            physics::Vector mouse;
            bool up;
            bool left;
            bool down;
            bool right;
        };

        Inputs inputs;

        bool updated = false;
        static constexpr uint8_t ID = 1;

        Camera(Entity *);

        void Tick();

        int32_t PlayerId();
        void PlayerId(int32_t);

        void WriteBinary(coder::Writer &writer);
        void FromBinary(coder::Reader &reader);
    };
}
