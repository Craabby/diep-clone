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
        static constexpr uint32_t ID = 2;
        bool updated;
        uint32_t ownerId;
        
        DECLARE_COMPONENT_FIELD(float, Physics, xPosition)
        DECLARE_COMPONENT_FIELD(float, Physics, yPosition)
        DECLARE_COMPONENT_FIELD(float, Physics, xVelocity)
        DECLARE_COMPONENT_FIELD(float, Physics, yVelocity)
        DECLARE_COMPONENT_FIELD(float, Physics, size)

        Physics(uint32_t ownerId);
        Physics(const Physics &) = delete;

		void Tick();
        void WriteBinary(Writer &);
        void ReadBinary(Reader &);
    };
}
