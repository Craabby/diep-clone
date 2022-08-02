#pragma once

#include <cstdint>
#include <vector>

#include <Shared/EntityComponentSystem/Component/Types.hh>

namespace shared
{
    struct Writer;
    struct Reader;
}

namespace shared::ecs::component
{
    struct Camera
    {
        static constexpr uint32_t ID = 0;
        bool updated;
        uint32_t ownerId;
        std::vector<uint32_t> view;
        DECLARE_COMPONENT_FIELD(float, Camera, x)
        DECLARE_COMPONENT_FIELD(float, Camera, y)
        DECLARE_COMPONENT_FIELD(float, Camera, fov)

        Camera(uint32_t ownerId);
        Camera(const Camera &) = delete;

        void WriteBinary(Writer &);
        void ReadBinary(Reader &);
    };
}
