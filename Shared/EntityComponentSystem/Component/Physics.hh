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
    struct Physics
    {
        static constexpr uint32_t ID = 1;
        bool updated;
        uint32_t ownerId;
        
        DECLARE_COMPONENT_FIELD(float, Physics, x)
        DECLARE_COMPONENT_FIELD(float, Physics, y)

        Physics(uint32_t ownerId);

        void WriteBinary(Writer &);
        void ReadBinary(Reader &);
    };
}
