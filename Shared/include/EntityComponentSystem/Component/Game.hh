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
        class Writer;
    }
}

namespace shared::ecs::component
{
    class Game
    {
        Entity *entity;

    public:
        uint32_t xAxisSize = 2400;
        uint32_t yAxisSize = 2400;

        bool updated = false;
        static constexpr uint8_t ID = 1;

        Game(Entity *);

        void WriteBinary(coder::Writer &writer);
    };
}
