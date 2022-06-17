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
    class Game
    {
        Entity *entity;

        uint32_t m_Width = 2400;
        uint32_t m_Height = 2400;

    public:
        bool updated = false;
        static constexpr uint8_t ID = 1;

        Game(Entity *);

        uint32_t Width();
        uint32_t Height();

        void Width(uint32_t);
        void Height(uint32_t);

        void WriteBinary(coder::Writer &writer);
        void FromBinary(coder::Reader &reader);
    };
}
