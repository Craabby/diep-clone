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
    class Basic
    {
        Entity *entity;

    public:
        bool updated = false;
        static constexpr uint8_t ID = 0;

        Basic(Entity *);

        void WriteBinary(coder::Writer &writer);
        void FromBinary(coder::Reader &reader);
    };
}
