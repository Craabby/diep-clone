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
        int32_t player;

    public:
        bool updated = false;
        static constexpr uint8_t ID = 1;

        Camera(Entity *);

        int32_t Player();
        void Player(int32_t);

        void WriteBinary(coder::Writer &writer);
        void FromBinary(coder::Reader &reader);
    };
}
