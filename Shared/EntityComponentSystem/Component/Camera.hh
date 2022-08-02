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
        DECLARE_COMPONENT_FIELD(float, Camera, x)
        DECLARE_COMPONENT_FIELD(float, Camera, y)
        DECLARE_COMPONENT_FIELD(float, Camera, fov)
        uint64_t magic = 2222222222222222;
        std::vector<uint32_t> view;

        Camera(uint32_t ownerId);
        Camera(const Camera &) = delete;

        void WriteBinary(Writer &);
        void ReadBinary(Reader &);
    };
}
