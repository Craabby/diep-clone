#pragma once

#include <cstdint>

#include <Shared/EntityComponentSystem/Component/Types.hh>

namespace shared
{
    class Writer;
    class Reader;
}

namespace shared::ecs::component
{
    class Physics
    {
    public:
        static constexpr uint32_t ID = 1;
        bool updated;
        uint32_t ownerId;
        
        Physics(uint32_t ownerId);

        DECLARE_COMPONENT_FIELD(float, X)
        DECLARE_COMPONENT_FIELD(float, Y)

        void WriteBinary(Writer &);
        void ReadBinary(Reader &);
    };
}
