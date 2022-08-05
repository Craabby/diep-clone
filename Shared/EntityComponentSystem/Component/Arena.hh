#pragma once

#include <cstdint>

#include <Shared/EntityComponentSystem/Component/Types.hh>

namespace shared
{
    struct Writer;
    struct Reader;
}

namespace shared::ecs::component
{
    struct Arena
    {
        static constexpr uint32_t ID = 0;
        bool updated;
        uint32_t ownerId;

        Arena(uint32_t ownerId);
        Arena(const Arena &) = delete;

        DECLARE_COMPONENT_FIELD(uint32_t, Arena, magicTest)

        void WriteBinary(Writer &);
        void ReadBinary(Reader &);
    };
}
