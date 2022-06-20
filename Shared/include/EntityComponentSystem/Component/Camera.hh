#pragma once

#include <cstdint>

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
        Entity *player;

    public:
        bool updated = false;
        static constexpr uint8_t ID = 1;

        Camera(Entity *);

        Entity *Player();
        void Player(Entity *);

        void WriteBinary(coder::Writer &writer);
        void FromBinary(coder::Reader &reader);
    };
}
