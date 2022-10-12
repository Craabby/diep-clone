#pragma once

#include <std2/cstdint.hh>
#include <std2/vector.hh>

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
        static constexpr uint32_t ID = 1;
        bool updated;
        uint32_t ownerId;
        std2::Vector<uint32_t> view;
        DECLARE_COMPONENT_FIELD(float, Camera, x)
        DECLARE_COMPONENT_FIELD(float, Camera, y)
        DECLARE_COMPONENT_FIELD(float, Camera, fov)
        DECLARE_COMPONENT_FIELD(uint32_t, Camera, child)

        Camera(uint32_t ownerId);
        Camera(const Camera &) = delete;

		void Tick();
        void WriteBinary(Writer &);
        void ReadBinary(Reader &);
    };
}
